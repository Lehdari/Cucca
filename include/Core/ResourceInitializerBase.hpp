/**
    Cucca Game Engine - Core - ResourceInitializerBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    ResourceInitializerBase is a dummy base class providing a virtual destructor
    for ResourceInitializers.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-29
**/


#ifndef CUCCA_CORE_RESOURCEINITIALIZERBASE_HPP
#define CUCCA_CORE_RESOURCEINITIALIZERBASE_HPP


namespace Cucca {

    class ResourceInitializerBase {
    public:
        ResourceInitializerBase(void) = default;
        ResourceInitializerBase(const ResourceInitializerBase&) = default;
        ResourceInitializerBase(ResourceInitializerBase&&) = default;
        ResourceInitializerBase& operator=(const ResourceInitializerBase&) & = default;
        ResourceInitializerBase& operator=(ResourceInitializerBase&&) & = default;
        virtual ~ResourceInitializerBase(void) {}
    };

} // namespace Cucca


#endif // CUCCA_CORE_RESOURCEINITIALIZERBASE_HPP
