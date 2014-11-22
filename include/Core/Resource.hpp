/**
    Cucca Game Engine - Core - Resource.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Resource is a CRTP class for user-defined resources. For each Resource
    user should also define a ResourceLoadInfo template specialization.
    This data structure is used to initialize the resource correctly.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-17
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include "ResourceBase.hpp"

#include <string>
#include <vector>


namespace Cucca {

    //  Typedefs
    typedef std::string ResourceId;


    //  Forward Declarations
    template <typename ResourceIdType_T>
    class ResourceManager;


    //  Structs and Classes
    struct ResourceInitInfoBase {
        virtual ~ResourceInitInfoBase(void) {}
    };


    template<typename ResourceType_T>
    struct ResourceInitInfo : public ResourceInitInfoBase {};


    template<typename ResourceType_T, typename ResourceIdType_T>
    class Resource : public ResourceBase { // TODO_RO5 (?)
    public:
        enum Status {
            STATUS_UNINITIALIZED,
            STATUS_INITIALIZED,
            STATUS_DESTROYED
        };

        Resource(void);

        void init(const ResourceInitInfo<ResourceType_T>& initInfo,
                  ResourceManager<ResourceIdType_T>& resourceManager,
                  const std::vector<ResourceIdType_T>& initResources,
                  const std::vector<ResourceIdType_T>& depResources);
        void destroy(void);

    protected:
        Status status_;
    };


    //  Member Definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    Resource<ResourceType_T, ResourceIdType_T>::Resource(void) :
        status_(STATUS_UNINITIALIZED)
    {}

    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::init(const ResourceInitInfo<ResourceType_T>& initInfo,
                                                          ResourceManager<ResourceIdType_T>& resourceManager,
                                                          const std::vector<ResourceIdType_T>& initResources,
                                                          const std::vector<ResourceIdType_T>& depResources) {
        static_cast<ResourceType_T>(this)->init(initInfo, resourceManager, initResources, depResources);
        status_ = STATUS_INITIALIZED;
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::destroy(void) {
        static_cast<ResourceType_T>(this)->destroy();
        status_ = STATUS_DESTROYED;
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCE_HPP
