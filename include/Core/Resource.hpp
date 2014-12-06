/**
    Cucca Game Engine - Core - Resource.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    Resource is a CRTP class for user-defined resources. It also provides
    enumerated status flag which is useful in multithreaded environment.
    A resource can be initialized and destroyed only once.

    To make a custom resource, inherit this class in CRTP manner
    ( class MyCustomResource : public Resource<MyCustomResource, ResourceId> )
    and implement init and destroy member functions.

    ResourceManager will call init and destroy asynchronously(if using a
    thread pool) so prefer them over constructor/destructor when CPU-intensive
    handling is required. This class also provides wrapped thread-safety for
    those functions.

    For each Resource user should also define a ResourceLoadInfo template
    specialization. This data structure is used to initialize the resource
    correctly.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-06
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include "ResourceBase.hpp"

#include <string>
#include <vector>


namespace Cucca {

    // Typedefs
    typedef std::string ResourceId;


    // Forward Declarations
    template <typename ResourceIdType_T>
    class ResourceManager;


    // Structs and Classes
    struct ResourceInitInfoBase {
        virtual ~ResourceInitInfoBase(void) {}
    };


    template<typename ResourceType_T>
    struct ResourceInitInfo : public ResourceInitInfoBase {};


    template<typename ResourceType_T, typename ResourceIdType_T>
    class Resource : public ResourceBase { // TODO_RO5 (?)
    public:
        void init(const ResourceInitInfo<ResourceType_T>& initInfo,
                  ResourceManager<ResourceIdType_T>& resourceManager,
                  const std::vector<ResourceIdType_T>& initResources,
                  const std::vector<ResourceIdType_T>& depResources);
        void destroy(void);
    };


    //  Member Definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::init(const ResourceInitInfo<ResourceType_T>& initInfo,
                                                          ResourceManager<ResourceIdType_T>& resourceManager,
                                                          const std::vector<ResourceIdType_T>& initResources,
                                                          const std::vector<ResourceIdType_T>& depResources) {
        if (status() != STATUS_UNINITIALIZED)
            return;
        setStatus(STATUS_INITIALIZING);
        static_cast<ResourceType_T*>(this)->init(initInfo, resourceManager, initResources, depResources);
        setStatus(STATUS_READY);
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::destroy(void) {
        if (status() != STATUS_READY)
            return;
        setStatus(STATUS_DESTROYING);
        static_cast<ResourceType_T*>(this)->destroy();
        setStatus(STATUS_DESTROYED);
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCE_HPP
