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
    @date       2015-01-29
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include "ResourceBase.hpp"
#include "ResourceInitializer.hpp"
#include "ResourceId.hpp"
#include "ResourcePointer.hpp"

#include <string>
#include <vector>


#define CUCCA_RESOURCE(RESOURCE_TYPE) class RESOURCE_TYPE : public Cucca::Resource<RESOURCE_TYPE, ResourceId>


namespace Cucca {

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

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCE_HPP
