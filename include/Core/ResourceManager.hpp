/**
    Cucca Game Engine - Core - ResourceManager.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceManager class defines an interface for managing resources.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-03
**/


#ifndef CUCCA_CORE_RESOURCEMANAGER_HPP
#define CUCCA_CORE_RESOURCEMANAGER_HPP


#include "Resource.hpp"
#include "ResourcePointer.hpp"

#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream> // TEMP


namespace Cucca {

    template<typename ResourceIdType_T>
    class ResourceManager {
    public:
        template<typename ResourceType_U, typename ResourceIdType_U>
        friend class ResourcePointer;

        ResourceManager(void) {}

        template<typename ResourceType_T>
        void addResourceInfo(const ResourceIdType_T& resourceId,
                             ResourceInitInfo<ResourceType_T>& initInfo,
                             const std::vector<ResourceIdType_T>& initResources,
                             const std::vector<ResourceIdType_T>& depResources);

        template<typename ResourceType_T>
        void loadResource(const ResourceIdType_T& resourceId);

        template<typename ResourceType_T>
        ResourcePointer<ResourceType_T, ResourceIdType_T> getResource(const ResourceIdType_T& resourceId);

        // TODO_IMPLEMENT
        /*template<typename ResourceType_T>
        shared_ptr<ResourceType_T> loadResource(const ResourceIdType_T& resourceId,
                                                ResourceType_T::InitInfo& initInfo,
                                                std::vector<const ResourceIdType_T>& initResources,
                                                std::vector<const ResourceIdType_T>& depResources);

        template<typename ResourceType_T>
        shared_ptr<ResourceType_T> getResource(const ResourceIdType_T& resourceId,
                                                ResourceType_T::InitInfo& initInfo,
                                                std::vector<const ResourceIdType_T>& initResources,
                                                std::vector<const ResourceIdType_T>& depResources);
        */

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

        //  Resource info and resource maps
        std::unordered_map<ResourceIdType_T, ResourceInfo> resourceInfos_;
        std::unordered_map<ResourceIdType_T, std::unique_ptr<ResourceBase>> resources_;

        //  Resource type id system. Similar to the one in the Node class.
        template<typename ResourceType_T>
        static int getResourceTypeId(void) {
            static unsigned numResourceTypes__ = 0;
            static int resourceTypeId__ = numResourceTypes__++;
            return resourceTypeId__;
        }

        //  Callback function for resource pointers to signal they've run out of references
        void pointerOutOfReferences(const ResourceIdType_T& resourceId);
    };


    // Member definitions
    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::addResourceInfo(const ResourceIdType_T& resourceId,
                                                            ResourceInitInfo<ResourceType_T>& initInfo,
                                                            const std::vector<ResourceIdType_T>& initResources,
                                                            const std::vector<ResourceIdType_T>& depResources) {
        ResourceInfo resourceInfo;
        resourceInfo.initInfo = std::unique_ptr<ResourceInitInfoBase>(new ResourceInitInfo<ResourceType_T>); // TODO_UNIQUE, TODO_ALLOCATOR
        *resourceInfo.initInfo = initInfo;
        resourceInfo.initResources = initResources;
        resourceInfo.depResources = depResources;
        resourceInfo.typeId = getResourceTypeId<ResourceType_T>();
        resourceInfo.referenceCount = std::unique_ptr<unsigned>(new unsigned(0));

        resourceInfos_[resourceId] = std::move(resourceInfo);
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    void ResourceManager<ResourceIdType_T>::loadResource(const ResourceIdType_T& resourceId) {
        if (resources_.find(resourceId) != resources_.end())
            return;

        if (resourceInfos_.find(resourceId) == resourceInfos_.end())
            throw "ResourceManager: cannot load resource (no resource info)"; // TODO_EXCEPTION: throw a proper exception

        auto resource = std::unique_ptr<ResourceBase>(new ResourceType_T());
        auto& resourceInfo = resourceInfos_[resourceId];
        static_cast<ResourceType_T*>(resource.get())->init(*static_cast<ResourceInitInfo<ResourceType_T>*>(resourceInfo.initInfo.get()),
                                                           resourceInfo.initResources,
                                                           resourceInfo.depResources);

        resources_[resourceId] = std::move(resource);
    }

    template<typename ResourceIdType_T>
    template<typename ResourceType_T>
    ResourcePointer<ResourceType_T, ResourceIdType_T> ResourceManager<ResourceIdType_T>::getResource(const ResourceIdType_T& resourceId) {
        if (resources_.find(resourceId) == resources_.end())
            loadResource<ResourceType_T>(resourceId);

        return ResourcePointer<ResourceType_T, ResourceIdType_T>(static_cast<ResourceType_T*>(resources_[resourceId].get()),
                                                                 resourceId,
                                                                 this,
                                                                 &ResourceManager<ResourceIdType_T>::pointerOutOfReferences,
                                                                 resourceInfos_[resourceId].referenceCount.get());
    }

    template<typename ResourceIdType_T>
    void ResourceManager<ResourceIdType_T>::pointerOutOfReferences(const ResourceIdType_T& resourceId) {
        std::cout << "Resource " << resourceId << " out of references" << std::endl; // TEMP
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEMANAGER_HPP
