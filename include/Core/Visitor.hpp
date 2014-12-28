/**
    Cucca Game Engine - Core - Visitor.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Visitor class defines a CRTP interface for manipulating components
    of nodes.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-07
**/


#ifndef CUCCA_CORE_VISITOR_HPP
#define CUCCA_CORE_VISITOR_HPP


#define CUCCA_VISITOR(VISITOR_TYPE, COMPONENT_TYPES...) class VISITOR_TYPE : public Cucca::Visitor<VISITOR_TYPE, COMPONENT_TYPES>


namespace Cucca {

    // Forward Declarations
    class Node;


    // Structs and Classes
    template<typename VisitorType_T, typename ...ComponentTypes_T>
    class VisitorInterface { };

    template<typename VisitorType_T, typename FirstComponentType_T, typename ...RestComponentTypes_T>
    class VisitorInterface<VisitorType_T, FirstComponentType_T, RestComponentTypes_T...> :
        public VisitorInterface<VisitorType_T, RestComponentTypes_T...> {
    public:
        /*  CRTP Implementation of this member function will be called when a visitor
            enters a node. */
        void nodeEnter(Node* node, FirstComponentType_T* component) {
            static_cast<VisitorType_T*>(this)->nodeEnter(node, component);
        }

        /*  CRTP Implementation of this member function will be called when a visitor
            exits a node. */
        void nodeExit(Node* node, FirstComponentType_T* component) {
            static_cast<VisitorType_T*>(this)->nodeExit(node, component);
        }
    };

    template<typename VisitorType_T>
    class VisitorInterface<VisitorType_T> { };

    template<typename VisitorType_T, typename ...ComponentTypes_T>
    class Visitor : public VisitorInterface<VisitorType_T, ComponentTypes_T...> { };

} // namespace Cucca


#endif // CUCCA_CORE_VISITOR_HPP
