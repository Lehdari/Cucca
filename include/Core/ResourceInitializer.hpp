/**
    Cucca Game Engine - Core - ResourceInitializer.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    For each Resource user should define a ResourceInitializer CRTP
    implementation. This class is used to initialize the resource
    correctly.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-29
**/


#ifndef CUCCA_CORE_RESOURCEINITIALIZER_HPP
#define CUCCA_CORE_RESOURCEINITIALIZER_HPP


#include "ResourceInitializerBase.hpp"
#include "ResourceBase.hpp"

#include <vector>


#define CUCCA_RESOURCEINITIALIZER(RESOURCEINITIALIZER_TYPE, RESOURCE_TYPE) class RESOURCEINITIALIZER_TYPE : public ResourceInitializer<RESOURCEINITIALIZER_TYPE, RESOURCE_TYPE, ResourceId>


namespace Cucca {

    // Forward Declarations
    template<typename ResourceIdType_T>
    class ResourceManager;


    //  Structs and classes
    template<typename ResourceInitializerType_T, typename ResourceType_T, typename ResourceIdType_T>
    struct ResourceInitializer : public ResourceInitializerBase {
    public:
        void init(ResourceType_T& resource,
                  std::vector<ResourceIdType_T> initResources,
                  std::vector<ResourceIdType_T> depResources,
                  ResourceManager<ResourceIdType_T>* resourceManager);
        void destroy(ResourceType_T& resource);
    };


    //  Member definitions
    template<typename ResourceInitializerType_T, typename ResourceType_T, typename ResourceIdType_T>
    void ResourceInitializer<ResourceInitializerType_T, ResourceType_T, ResourceIdType_T>::init(ResourceType_T& resource,
                                                                                                std::vector<ResourceIdType_T> initResources,
                                                                                                std::vector<ResourceIdType_T> depResources,
                                                                                                ResourceManager<ResourceIdType_T>* resourceManager) {
        if (resource.status() != ResourceBase::STATUS_UNINITIALIZED)
            return;
        resource.setStatus(ResourceBase::STATUS_INITIALIZING);
        static_cast<ResourceInitializerType_T*>(this)->init(resource, initResources, depResources, resourceManager);
        resource.setStatus(ResourceBase::STATUS_READY);
    }

    template<typename ResourceInitializerType_T, typename ResourceType_T, typename ResourceIdType_T>
    void ResourceInitializer<ResourceInitializerType_T, ResourceType_T, ResourceIdType_T>::destroy(ResourceType_T& resource) {
        if (resource.status() != ResourceBase::STATUS_READY)
            return;
        resource.setStatus(ResourceBase::STATUS_DESTROYING);
        static_cast<ResourceInitializerType_T*>(this)->destroy();
        resource.setStatus(ResourceBase::STATUS_DESTROYED);
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEINITIALIZER_HPP
