/**
    Cucca Game Engine - Core - EventComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-10
**/


#include "../../include/Core/ResourceBase.hpp"


using namespace Cucca;


ResourceBase::ResourceBase(void) :
    status_(STATUS_UNINITIALIZED),
    numThreadsWaitingForStatus_(0),
    movedTo_(nullptr)
{}

ResourceBase::ResourceBase(ResourceBase&& other) :
    status_(other.status()),
    numThreadsWaitingForStatus_(0),
    movedTo_(nullptr)
{
    other.move(this);
}

ResourceBase& ResourceBase::operator=(ResourceBase&& other) {
    move(nullptr);

    status_ = other.status();
    numThreadsWaitingForStatus_ = 0;
    movedTo_ = nullptr;

    other.move(this);
    return *this;
}

ResourceBase::Status ResourceBase::status(void) {
    std::lock_guard<std::mutex> lock(statusMutex_);
    return status_;
}

ResourceBase::~ResourceBase(void) {
    move(nullptr);
}

void ResourceBase::setStatus(ResourceBase::Status status) {
    {
        std::lock_guard<std::mutex> lock(statusMutex_);
        status_ = status;
    }
    statusCV_.notify_all();
}

bool ResourceBase::waitForStatus(ResourceBase* obj, ResourceBase::Status status) {
    ++(obj->numThreadsWaitingForStatus_);

    while (obj->status() != status) {
        std::unique_lock<std::mutex> lock(obj->statusMutex_);
        obj->statusCV_.wait(lock, [obj, status]{ return obj->status_ == status || obj->status_ == STATUS_MOVED; });

        if (obj->status_ == STATUS_MOVED) {
            ResourceBase* movedTo;
            {
                std::lock_guard<std::mutex> lock2(obj->movedMutex_);
                movedTo = obj->movedTo_;
            }

            if (--(obj->numThreadsWaitingForStatus_) == 0)
                obj->movedCV_.notify_all();

            if (movedTo) {
                obj = movedTo;
                ++(obj->numThreadsWaitingForStatus_);
            }
            else {
                return false;
            }
        }
    }

    --(obj->numThreadsWaitingForStatus_);
    return true;
}

void ResourceBase::move(ResourceBase* moveTo) {
    {
        std::lock_guard<std::mutex> lock(movedMutex_);
        movedTo_ = moveTo;
    }
    {
        std::unique_lock<std::mutex> lock(statusMutex_);
        status_ = STATUS_MOVED;
        statusCV_.notify_all();
    }
    //  wait for all the waiting threads to stop waiting
    std::unique_lock<std::mutex> lock(movedMutex_);
    movedCV_.wait(lock, [this]{ return numThreadsWaitingForStatus_ == 0; });
}
