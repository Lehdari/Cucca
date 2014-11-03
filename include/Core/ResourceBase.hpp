/**
    Cucca Game Engine - Core - ResourceBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceBase class is just a dummy base class for the user-defined
    components.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-02
**/


#ifndef CUCCA_CORE_RESOURCEBASE_HPP
#define CUCCA_CORE_RESOURCEBASE_HPP


namespace Cucca {

    class ResourceBase {
    public:
        ResourceBase(void) = default;
        ResourceBase(const ResourceBase&) = default;
        ResourceBase(ResourceBase&&) = default;
        ResourceBase& operator=(const ResourceBase&) & = default;
        ResourceBase& operator=(ResourceBase&&) & = default;
        virtual ~ResourceBase(void) {}
    };

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEBASE_HPP
