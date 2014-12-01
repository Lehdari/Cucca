/**
    Cucca Game Engine - Core - ResourceManager.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceManager class defines an interface for managing resources.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-01
**/


#ifndef CUCCA_CORE_RESOURCEMANAGER_HPP
#define CUCCA_CORE_RESOURCEMANAGER_HPP


#include "Resource.hpp"
#include "ResourcePointer.hpp"
#include "ThreadPool.hpp"

#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>


namespace Cucca {

    template<typename ResourceIdType_T>
    class ResourceManager {
    public:
        template<typename ResourceType_U, typename ResourceIdType_U>
        friend class ResourcePointer;

        ResourceManager(void);
        ResourceManager(ThreadPool* threadPool);

        //  Resource infos are required to load resources with their identifier
        template<typename ResourceType_T>
        void addResourceInfo(const ResourceIdType_T& resourceId,
                             ResourceInitInfo<ResourceType_T>& initInfo,
                             const std::vector<ResourceIdType_T>& initResources,
                             const std::vector<ResourceIdType_T>& depResources);

        template<typename ResourceType_T>
        void addResourceInfo(const ResourceIdType_T& resourceId,
                             ResourceInitInfo<ResourceType_T>&& initInfo,
                             std::vector<ResourceIdType_T>&& initResources,
                             std::vector<ResourceIdType_T>&& depResources);

        //  Loads resource with calling thread
        template<typename ResourceType_T>
        void loadResource(const ResourceIdType_T& resourceId);

        //  Loads resource with thread pool, returns instantly. Pointer to running ThreadPool required
        //template<typename ResourceType_T>
        //void loadResourceAsync(const ResourceIdType_T& resourceId);

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
            std::unique_ptr<ResourceInitInfoBase> initInfo;
            std::vector<ResourceIdType_T> initResources;
            std::vector<ResourceIdType_T> depResources;
            unsigned typeId;
            std::unique_ptr<unsigned> referenceCount;
        };

        //  Resource type id system. Similar to the one in the Node class.
        template<typename ResourceType_T>
        static int getResourceTypeId(void) {
            static unsigned numResourceTypes__ = 0;
            static int resourceTypeId__ = numResourceTypes__++;
            return resourceTypeId__;
        }

        template<typename ResourceType_T>
        void initResource(const ResourceIdType_T& resourceId);

        //  Callback function for resource pointers to signal they've run out of references
        void pointerOutOfReferences(const ResourceIdType_T& resourceId);

        //  Resource info and resource maps
        std::unordered_map<ResourceIdType_T, ResourceInfo> resourceInfos_;
        std::unordered_map<ResourceIdType_T, std::unique_ptr<ResourceBase>> resources_;
        std::recursive_mutex resourceMutex_;

        //  Asynchronous loading stuff
        ThreadPool* threadPool_;

        /*template<typename ResourceIdType_U>
        class ResourceInitializer : public Task {
        public:
            ResourceInitializer(ResourceManager& resourceManager, const ResourceIdType_U& resourceId) :
                Task(task(this, &this->initResource)),
                resourceManager_(resourceManager), resourceId_(resourceId)
            {}

            void initResource(void) {
                resourceManager_->initResource(resourceId_);
            }
        private:
            ResourceManager& resourceManager_;
            const ResourceIdType_U& resourceId_;
        };*/
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
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::addResourceInfo(const ResourceIdType_T& resourceId,
                                                            ResourceInitInfo<ResourceType_T>& initInfo,
                                                            const std::vector<ResourceIdType_T>& initResources,
                                                            const std::vector<ResourceIdType_T>& depResources) {
        ResourceInfo resourceInfo;
        resourceInfo.initInfo = std::unique_ptr<ResourceInitInfoBase>(new ResourceInitInfo<ResourceType_T>(initInfo)); // TODO_UNIQUE, TODO_ALLOCATOR
        resourceInfo.initResources = initResources;
        resourceInfo.depResources = depResources;
        resourceInfo.typeId = getResourceTypeId<ResourceType_T>();
        resourceInfo.referenceCount = std::unique_ptr<unsigned>(new unsigned(0));

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
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::loadResource(const ResourceIdType_T& resourceId) {
        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            if (resources_.find(resourceId) != resources_.end())
                return;

            if (resourceInfos_.find(resourceId) == resourceInfos_.end())
                throw "ResourceManager: unable to load resource (no resource info)"; // TODO_EXCEPTION: throw a proper exception

            resources_.insert(std::make_pair(resourceId, std::unique_ptr<ResourceBase>(new ResourceType_T())));
        }

        if (threadPool_ && threadPool_->status() == ThreadPool::STATUS_RUNNING) {
            threadPool_->pushTask(Task(this, &ResourceManager<ResourceIdType_T>::initResource<ResourceType_T>, resourceId));
        }
        else
            initResource<ResourceType_T>(resourceId);
    }

    /*template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::loadResourceAsync(const ResourceIdType_T& resourceId) {
        if (resources_.find(resourceId) != resources_.end())
            return;

        if (resourceInfos_.find(resourceId) == resourceInfos_.end())
            throw "ResourceManager: unable to load resource (no resource info)"; // TODO_EXCEPTION: throw a proper exception

        auto resource = std::unique_ptr<ResourceBase>(new ResourceType_T());
        auto& resourceInfo = resourceInfos_[resourceId];
        static_cast<ResourceType_T*>(resource.get())->init(*static_cast<ResourceInitInfo<ResourceType_T>*>(resourceInfo.initInfo.get()),
                                                           *this,
                                                           resourceInfo.initResources,
                                                           resourceInfo.depResources);

        resources_[resourceId] = std::move(resource);
    }*/

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T> ResourceManager<ResourceIdType_T>::getResource(const ResourceIdType_T& resourceId) {
        std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

        if (resources_.find(resourceId) == resources_.end())
            loadResource<ResourceType_T>(resourceId);

        return ResourcePointer<ResourceType_T, ResourceIdType_T>(static_cast<ResourceType_T*>(resources_[resourceId].get()),
                                                                 resourceId,
                                                                 this,
                                                                 &ResourceManager<ResourceIdType_T>::pointerOutOfReferences,
                                                                 resourceInfos_[resourceId].referenceCount.get());
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::initResource(const ResourceIdType_T& resourceId) {
        ResourceInitInfoBase* initInfo;
        std::vector<ResourceIdType_T> initResources;
        std::vector<ResourceIdType_T> depResources;

        ResourceType_T* resource;

        {
            std::lock_guard<std::recursive_mutex> lock(resourceMutex_);

            initInfo = resourceInfos_[resourceId].initInfo.get();
            initResources = resourceInfos_[resourceId].initResources;
            depResources = resourceInfos_[resourceId].depResources;

            resource = static_cast<ResourceType_T*>(resources_[resourceId].get());
        }
        //  resource is just a pointer to a resource and resourceInfo was copied, so
        //  now it should be safe to initialize the resource without mutexing
        resource->init(*static_cast<ResourceInitInfo<ResourceType_T>*>(initInfo),
                       *this,
                       initResources,
                       depResources);
    }

    template<typename ResourceIdType_T>
    void ResourceManager<ResourceIdType_T>::pointerOutOfReferences(const ResourceIdType_T& resourceId) {
        // TODO_IMPLEMENT
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEMANAGER_HPP
