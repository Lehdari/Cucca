/**
    Cucca Game Engine - Core - ResourceManager.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceManager class defines an interface for managing resources.

    @version    0.1
    @author     Miika Lehtim�ki
    @date       2014-12-06
**/


#ifndef CUCCA_CORE_RESOURCEMANAGER_HPP
#define CUCCA_CORE_RESOURCEMANAGER_HPP


#include "Resource.hpp"
#include "ResourcePointer.hpp"
#include "ThreadPool.hpp"

#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>
#include <cstdio> // TEMP


namespace Cucca {

    template<typename ResourceIdType_T>
    class ResourceManager {
    public:
        template<typename ResourceType_U, typename ResourceIdType_U>
        friend class ResourcePointer;

        ResourceManager(void);
        ResourceManager(ThreadPool* threadPool);
        ~ResourceManager(void);

        //  Resource infos are required to load resources with their identifier
        template<typename ResourceType_T>
        void addResourceInfo(const ResourceIdType_T& resourceId,
                             ResourceInitInfo<ResourceType_T>& initInfo,
                             const std::vector<ResourceIdType_T>& initResources = std::vector<ResourceIdType_T>(),
                             const std::vector<ResourceIdType_T>& depResources = std::vector<ResourceIdType_T>());

        template<typename ResourceType_T>
        void addResourceInfo(const ResourceIdType_T& resourceId,
                             ResourceInitInfo<ResourceType_T>&& initInfo,
                             std::vector<ResourceIdType_T>&& initResources = std::vector<ResourceIdType_T>(),
                             std::vector<ResourceIdType_T>&& depResources = std::vector<ResourceIdType_T>());

        //  Loads resource asynchronously if pointer to running thread pool has been provided,
        //  synchronously with calling thread otherwise. Forcing synchronous loading also possible.
        void loadResource(const ResourceIdType_T& resourceId, bool forceSynchronous = false);

        //  For getting the actual resource. Loads it with calling thread if it doesn't exist
        template<typename ResourceType_T>
        ResourcePointer<ResourceType_T, ResourceIdType_T> getResource(const ResourceIdType_T& resourceId);

        //  ResourceManager is uncopyable and immovable
        ResourceManager(const ResourceManager<ResourceIdType_T>& resourceManager) = delete;
        ResourceManager(ResourceManager<ResourceIdType_T>&& resourceManager) = delete;
        ResourceManager& operator=(const ResourceManager<ResourceIdType_T>& resourceManager) = delete;
        ResourceManager& operator=(ResourceManager<ResourceIdType_T>&& resourceManager) = delete;

    private:
        struct ResourceInfo {
            //  static data
            std::unique_ptr<ResourceInitInfoBase> initInfo;
            std::vector<ResourceIdType_T> initResources;
            std::vector<ResourceIdType_T> depResources;
            //unsigned typeId;

            //  dynamic data (updated during the lifetime of Resource)
            std::unique_ptr<int> referenceCount;
            std::function<void(const ResourceId&)> init; // call to ResourceManager::initResource
            std::function<void(ResourceBase*)> destroy; // call to ResourceManager::destroyResource
        };

        template<typename ResourceType_T>
        void initResource(const ResourceId& resourceId);

        template<typename ResourceType_T>
        void destroyResource(ResourceBase* resource);

        //  Callback function for resource pointers to signal they've run out of references
        template<typename ResourceType_T>
        void pointerOutOfReferences(ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer);

        //  Resource info and resource maps
        std::unordered_map<ResourceIdType_T, ResourceInfo> resourceInfos_;
        std::unordered_map<ResourceIdType_T, std::unique_ptr<ResourceBase>> resources_;
        std::recursive_mutex resourceMutex_;

        //  Asynchronous loading stuff
        ThreadPool* threadPool_;
    };


    // Member definitions
    template<typename ResourceIdType_T>
    ResourceManager<ResourceIdType_T>::ResourceManager(void) :
        threadPool_(nullptr)
    {}

    template<typename ResourceIdType_T>
    ResourceManager<ResourceIdType_T>::ResourceManager(ThreadPool* threadPool) :
        threadPool_(threadPool)
    {}

    template<typename ResourceIdType_T>
    ResourceManager<ResourceIdType_T>::~ResourceManager(void) {
        std::lock_guard<std::recursive_mutex> lock(resourceMutex_); // no changes allowed during destructor

        //  remove any pending tasks that'd cause changes to ResourceManager or resources which are
        //  about to be destructed
        if (threadPool_ && threadPool_->status() == ThreadPool::STATUS_RUNNING)
            threadPool_->removeTasks(Task::FLAG_RESOURCEMANAGER);

        for (auto& resourceInfo : resourceInfos_) { // TODO make smarter, asynchronous(multithreaded)
            resourceInfo.second.destroy(resources_[resourceInfo.first].get()); // call destroy member function stored in info

            //  these will exist until all of the resources have been deleted (member destruction order),
            //  so in case of ResourcePointer going out of references it should go to negative
            //  values and not call pointerOutOfReferences as it would crash the whole application
            //  (handling data structure while destruction)
            *resourceInfo.second.referenceCount = 0;
        }
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::addResourceInfo(const ResourceIdType_T& resourceId,
                                                            ResourceInitInfo<ResourceType_T>& initInfo,
                                                            const std::vector<ResourceIdType_T>& initResources,
                                                            const std::vector<ResourceIdType_T>& depResources) {
        ResourceInfo resourceInfo;
        resourceInfo.initInfo = std::unique_ptr<ResourceInitInfoBase>(new ResourceInitInfo<ResourceType_T>(initInfo)); // TODO_UNIQUE, TODO_ALLOCATOR
        resourceInfo.initResources = initResources;
        resourceInfo.depResources = depResources;
        //resourceInfo.typeId = getResourceTypeId<ResourceType_T>();
        resourceInfo.referenceCount = std::unique_ptr<int>(new int(0));
        resourceInfo.init = std::bind(&ResourceManager<ResourceIdType_T>::initResource<ResourceType_T>, this, std::placeholders::_1);
        resourceInfo.destroy = std::bind(&ResourceManager<ResourceIdType_T>::destroyResource<ResourceType_T>, this, std::placeholders::_1);

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);
            resourceInfos_[resourceId] = std::move(resourceInfo);
        }
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::addResourceInfo(const ResourceIdType_T& resourceId,
                                                            ResourceInitInfo<ResourceType_T>&& initInfo,
                                                            std::vector<ResourceIdType_T>&& initResources,
                                                            std::vector<ResourceIdType_T>&& depResources) {
        addResourceInfo(resourceId, initInfo, initResources, depResources);
    }

    template<typename ResourceIdType_T>
    void ResourceManager<ResourceIdType_T>::loadResource(const ResourceIdType_T& resourceId, bool forceSynchronous) {
        std::function<void(const ResourceId&)> init;

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            if (resources_.find(resourceId) != resources_.end())
                return;

            if (resourceInfos_.find(resourceId) == resourceInfos_.end())
                throw "ResourceManager: unable to load resource (no resource info)"; // TODO_EXCEPTION: throw a proper exception

            //  Add just pointer to ResourceBase (it has status info though)
            resources_.insert(std::make_pair(resourceId, std::unique_ptr<ResourceBase>(new ResourceBase())));
            init = resourceInfos_[resourceId].init;
        }

        if (!forceSynchronous && threadPool_ && threadPool_->status() == ThreadPool::STATUS_RUNNING) {
            threadPool_->pushTask(Task(Task::FLAG_RESOURCEMANAGER, init, resourceId));
        }
        else
            init(resourceId);
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T> ResourceManager<ResourceIdType_T>::getResource(const ResourceIdType_T& resourceId) {
        std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

        if (resources_.find(resourceId) == resources_.end())
            loadResource(resourceId, true);

        //  TODO: wait before the resource has been loaded, implement CV notification

        return ResourcePointer<ResourceType_T, ResourceIdType_T>(static_cast<ResourceType_T*>(resources_[resourceId].get()),
                                                                 resourceId,
                                                                 this,
                                                                 &ResourceManager<ResourceIdType_T>::pointerOutOfReferences<ResourceType_T>,
                                                                 resourceInfos_[resourceId].referenceCount.get());
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::initResource(const ResourceId& resourceId) {
        printf("Initializing %s\n", resourceId.c_str());

        Resource<ResourceType_T, ResourceIdType_T>* resource;

        ResourceInitInfoBase* initInfo;
        std::vector<ResourceIdType_T> initResources;
        std::vector<ResourceIdType_T> depResources;

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            //  TODO_EXCEPTION?: check if ResourceBase with given id exists, throw an exception if not

            initInfo = resourceInfos_[resourceId].initInfo.get();
            initResources = resourceInfos_[resourceId].initResources;
            depResources = resourceInfos_[resourceId].depResources;
        }

        //  load dependency and initialization resources
        for (auto& depResourceId : depResources)
            loadResource(depResourceId);

        for (auto& initResourceId : initResources)
            loadResource(initResourceId);

        //  wait until all dependency and initialization resources have been loaded
        std::vector<ResourceBase*> depResourcesPtrs, initResourcesPtrs;

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            for (auto& depResourceId : depResources)
                depResourcesPtrs.push_back(resources_[depResourceId].get());

            for (auto& initResourceId : initResources)
                initResourcesPtrs.push_back(resources_[initResourceId].get());
        }

        for (auto& ptr : depResourcesPtrs)
            ResourceBase::waitForStatus(ptr, ResourceBase::STATUS_READY);

        for (auto& ptr : initResourcesPtrs)
            ResourceBase::waitForStatus(ptr, ResourceBase::STATUS_READY);

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            resources_[resourceId] = std::unique_ptr<ResourceBase>(new ResourceType_T(std::move(*(resources_[resourceId].get()))));
            resource = static_cast<Resource<ResourceType_T, ResourceIdType_T>*>(resources_[resourceId].get());
        }

        //  now it should be safe to initialize the resource without mutexing
        resource->init(*static_cast<ResourceInitInfo<ResourceType_T>*>(initInfo),
                       *this,
                       initResources,
                       depResources);
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::destroyResource(ResourceBase* resource) {
        static_cast<Resource<ResourceType_T, ResourceIdType_T>*>(resource)->destroy();
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::pointerOutOfReferences(ResourcePointer<ResourceType_T, ResourceIdType_T>& resourcePointer) {
        printf("%s: pointer out of references\n", resourcePointer.getId().c_str()); // TEMP

        // TODO_IMPLEMENT
        // for now, we just delete the resource once it goes out of references.
        // make buffer for unreferenced resources and implement lazy uninitialization
        ResourceBase* resource;
        std::function<void(ResourceBase*)> destroy;

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            if (resources_.find(resourcePointer.getId()) == resources_.end()) {
                return;
            }

            resource = resources_[resourcePointer.getId()].get();
            destroy = resourceInfos_[resourcePointer.getId()].destroy;
        }

        if (threadPool_ && threadPool_->status() == ThreadPool::STATUS_RUNNING)
            threadPool_->pushTask(Task(Task::FLAG_RESOURCEMANAGER, destroy, resource));
        else
            destroy(resource);
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEMANAGER_HPP
