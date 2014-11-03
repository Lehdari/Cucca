/**
    Cucca Game Engine - Core - Resource.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Resource is a CRTP class for user-defined resources. For each Resource
    user should also define a ResourceLoadInfo template specialization.
    This data structure is used to initialize the resource correctly.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-03
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include "ResourceBase.hpp"

#include <vector>


namespace Cucca {

    struct ResourceInitInfoBase {
        virtual ~ResourceInitInfoBase(void) {}
    };


    template<typename ResourceType_T>
    struct ResourceInitInfo : public ResourceInitInfoBase {};


    template<typename ResourceType_T, typename ResourceIdType_T>
    class Resource : public ResourceBase {
    public:
        void init(ResourceInitInfo<ResourceType_T>& initInfo,
                  const std::vector<ResourceIdType_T>& initResources,
                  const std::vector<ResourceIdType_T>& depResources);
        void destroy(void);
    };


    // Member definitions
    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::init(ResourceInitInfo<ResourceType_T>& initInfo,
                                                          const std::vector<ResourceIdType_T>& initResources,
                                                          const std::vector<ResourceIdType_T>& depResources) {
        static_cast<ResourceType_T>(this)->init(initInfo, initResources, depResources);
    }

    template<typename ResourceType_T, typename ResourceIdType_T>
    void Resource<ResourceType_T, ResourceIdType_T>::destroy(void) {
        static_cast<ResourceType_T>(this)->destroy();
    }

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCE_HPP
