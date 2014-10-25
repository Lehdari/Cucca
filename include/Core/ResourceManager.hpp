/**
    Cucca Game Engine - Core - ResourceBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.



    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-26
**/


#ifndef CUCCA_CORE_RESOURCEMANAGER_HPP
#define CUCCA_CORE_RESOURCEMANAGER_HPP


#include "Resource.hpp"


class ResourceManager {
public:

    template<typename ResourceType_T>
    shared_ptr<Resource<ResourceType_T>> giveResource(ResourceInfo<ResourceType_T>::Info info) {
        return shared_ptr<ResourceType_T>(nullptr);
    }
};


#endif // CUCCA_CORE_RESOURCEMANAGER_HPP
