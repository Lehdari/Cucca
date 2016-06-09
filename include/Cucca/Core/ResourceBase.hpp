/**
    Cucca Game Engine - Core - ResourceBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    ResourceBase class acts as a base for user-defined CRTP resources
    providing thread-safe status information interface including
    move semantics.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-10
**/


#ifndef CUCCA_CORE_RESOURCEBASE_HPP
#define CUCCA_CORE_RESOURCEBASE_HPP


#include <mutex>
#include <condition_variable>
#include <atomic>


namespace Cucca {

    class ResourceBase {
    public:
        enum Status {
            STATUS_UNINITIALIZED,
            STATUS_INITIALIZING,
            STATUS_READY,
            STATUS_DESTROYING,
            STATUS_DESTROYED,
            STATUS_MOVED
        };

        ResourceBase(void);
        ResourceBase(ResourceBase&&);
        ResourceBase& operator=(ResourceBase&&);
        virtual ~ResourceBase(void);

        /// ResourceBase is uncopyable (why would you want to copy a resource anyway)
        ResourceBase(const ResourceBase&) = delete;
        ResourceBase& operator=(const ResourceBase&) & = delete;

        Status status(void);
        /// Wait for ResourceBase to reach a status.
        /// Returns true if asked status was reached, false if object was moved
        static bool waitForStatus(ResourceBase* obj, Status status);

    protected:
        Status status_;
        std::mutex statusMutex_;
        std::condition_variable statusCV_;

        std::atomic_uint numThreadsWaitingForStatus_;

        //  Required when moving the object
        ResourceBase* movedTo_;
        std::mutex movedMutex_;
        std::condition_variable movedCV_;

        void setStatus(Status status);
        void move(ResourceBase* moveTo);
    };

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEBASE_HPP
