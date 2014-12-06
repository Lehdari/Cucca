/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-06
**/

#include "../../include/Core/ResourceBase.hpp"


using namespace Cucca;


ResourceBase::ResourceBase(void) :
    status_(STATUS_UNINITIALIZED)
{}

ResourceBase::Status ResourceBase::status(void) {
    std::lock_guard<std::mutex> lock(statusMutex_);
    return status_;
}

void ResourceBase::setStatus(ResourceBase::Status status) {
    std::lock_guard<std::mutex> lock(statusMutex_);
    status_ = status;
}
