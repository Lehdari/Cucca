/**
    Cucca Game Engine - Core - ResourceBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    ResourceBase class is a dummy-ish base class with some status info
    for the user-defined resources.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-06
**/


#ifndef CUCCA_CORE_RESOURCEBASE_HPP
#define CUCCA_CORE_RESOURCEBASE_HPP


#include <mutex>


namespace Cucca {

    class ResourceBase {
    public:
        enum Status {
            STATUS_UNINITIALIZED,
            STATUS_INITIALIZING,
            STATUS_READY,
            STATUS_DESTROYING,
            STATUS_DESTROYED
        };

        ResourceBase(void);
        ResourceBase(const ResourceBase&) = default;
        ResourceBase(ResourceBase&&) = default;
        ResourceBase& operator=(const ResourceBase&) & = default;
        ResourceBase& operator=(ResourceBase&&) & = default;
        virtual ~ResourceBase(void) {}

        Status status(void);

    protected:
        Status status_;
        std::mutex statusMutex_;

        void setStatus(Status status);
    };

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEBASE_HPP
