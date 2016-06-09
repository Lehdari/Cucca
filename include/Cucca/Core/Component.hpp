/**
    Cucca Game Engine - Core - Component.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Component class is just a dummy base class for the user-defined
    components.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-02
**/


#ifndef CUCCA_CORE_COMPONENT_HPP
#define CUCCA_CORE_COMPONENT_HPP


namespace Cucca {

    class Component {
    public:
        Component(void) = default;
        Component(const Component&) = default;
        Component(Component&&) = default;
        Component& operator=(const Component&) & = default;
        Component& operator=(Component&&) & = default;
        virtual ~Component(void) {}
    };

} // namespace Cucca


#endif // CUCCA_CORE_COMPONENT_HPP
