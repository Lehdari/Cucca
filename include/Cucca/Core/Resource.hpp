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


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include <Cucca/Debug/Debug.hpp>
#include <Cucca/Core/ResourceBase.hpp>
#include <Cucca/Core/ResourceId.hpp>
#include <Cucca/Core/ResourcePointer.hpp>

#include <vector>


//  macro for correct CRTP usage
#define CUCCA_RESOURCE(RESOURCE_TYPE) class RESOURCE_TYPE : public Cucca::Resource<RESOURCE_TYPE, ResourceId>

//  macro for resource init/destroy member functions (identical to every resource)
#define CUCCA_RESOURCE_INIT_DESTROY_DECL template<typename ResourceInitInfoType_T>\
                                         void init(const ResourceInitInfoType_T& initInfo,\
                                                   const std::vector<ResourceId>& initResources,\
                                                   const std::vector<ResourceId>& depResources,\
                                                   ResourceManager<ResourceId>* resourceManager);\
                                         template<typename ResourceInitInfoType_T>\
                                         void destroy(void);\

//  macros for init/destroy implementations in resource initialization files
#define CUCCA_RESOURCE_INIT(RESOURCE_TYPE, RESOURCE_INIT_INFO_TYPE) template<> inline void Cucca::RESOURCE_TYPE::init<RESOURCE_INIT_INFO_TYPE>(const RESOURCE_INIT_INFO_TYPE& initInfo,\
                                                                                                                                               const std::vector<ResourceId>& initResources,\
                                                                                                                                               const std::vector<ResourceId>& depResources,\
                                                                                                                                               ResourceManager<ResourceId>* resourceManager)
#define CUCCA_RESOURCE_DESTROY(RESOURCE_TYPE, RESOURCE_INIT_INFO_TYPE) template<> inline void Cucca::RESOURCE_TYPE::destroy<RESOURCE_INIT_INFO_TYPE>(void)


namespace Cucca {

    // Forward Declarations
    template<typename ResourceIdType_T>
    class ResourceManager;


    // Structs and Classes
    template<typename ResourceType_T, typename ResourceIdType_T>
    class Resource : public ResourceBase { // TODO_RO5 (?)
    public:
        Resource(void);

        Resource(ResourceBase&&);

        Resource(Resource&&) = default;
        Resource& operator=(Resource&&) = default;
        virtual ~Resource(void) = default;

        /// ResourceBase is uncopyable (why would you want to copy a resource anyway)
        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) & = delete;

        template<typename ResourceInitInfoType_T>
        void init(ResourceInitInfoType_T initInfo,
                  std::vector<ResourceIdType_T> initResources,
                  std::vector<ResourceIdType_T> depResources,
                  ResourceManager<ResourceIdType_T>* resourceManager);

        template<typename ResourceInitInfoType_T>
        void destroy(void);
    };


    //  Member Definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    Resource<ResourceType_T, ResourceIdType_T>::Resource(void) :
        ResourceBase()
    {}

    template<typename ResourceType_T, typename ResourceIdType_T>
    Resource<ResourceType_T, ResourceIdType_T>::Resource(ResourceBase&& other) :
        ResourceBase(std::move(other))
    {}

    template<typename ResourceType_T, typename ResourceIdType_T>
    template<typename ResourceInitInfoType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::init(ResourceInitInfoType_T initInfo,
                                                          std::vector<ResourceIdType_T> initResources,
                                                          std::vector<ResourceIdType_T> depResources,
                                                          ResourceManager<ResourceIdType_T>* resourceManager) {
        if (status() != STATUS_UNINITIALIZED)
            return;
        setStatus(STATUS_INITIALIZING);
        static_cast<ResourceType_T*>(this)->init(initInfo, initResources, depResources, resourceManager);
        setStatus(STATUS_READY);
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    template<typename ResourceInitInfoType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::destroy(void) {
        if (status() != STATUS_READY)
            return;
        setStatus(STATUS_DESTROYING);
        static_cast<ResourceType_T*>(this)->destroy<ResourceInitInfoType_T>();
        setStatus(STATUS_DESTROYED);
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCE_HPP
