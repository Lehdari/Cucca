/**
    Cucca Game Engine - Core - ResourceInitInfoBase.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    ResourceInitInfoBase is just a dummy class providing virtual
    destructor for resource initialization info structs.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-03
**/


#ifndef CUCCA_CORE_RESOURCEINITINFOBASE_HPP
#define CUCCA_CORE_RESOURCEINITINFOBASE_HPP


namespace Cucca {

    struct ResourceInitInfoBase {
        ResourceInitInfoBase(void) = default;
        ResourceInitInfoBase(const ResourceInitInfoBase&) = default;
        ResourceInitInfoBase(ResourceInitInfoBase&&) = default;
        ResourceInitInfoBase& operator=(const ResourceInitInfoBase&) & = default;
        ResourceInitInfoBase& operator=(ResourceInitInfoBase&&) & = default;
        virtual ~ResourceInitInfoBase(void) {}
    };

}


#endif // CUCCA_CORE_RESOURCEINITINFOBASE_HPP
