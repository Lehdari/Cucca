/**
    Cucca Game Engine - Core - Resource.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Resource class stores resources of arbitrary type.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-26
**/


#ifndef CUCCA_CORE_RESOURCE_HPP
#define CUCCA_CORE_RESOURCE_HPP


#include "ResourceBase.hpp"


namespace Cucca {
    template<typename ResourceType_T>
    class Resource : public ResourceBase {
    public:
        struct Info {
        };

        Resource(const ResourceType_T& resource) :
            ResourceBase(resource),
            resource_(std::unique_ptr<ResourceType_T>(new ResourceType_T(resource)))
        {}

        //  Get resource pointer
        ResourceType_T* getResource(void) const {
            return resource_.get();
        }

    private:
        //  Stored resource
        std::unique_ptr<ResourceType_T> resource_;
    };
}

#endif // CUCCA_CORE_RESOURCE_HPP
