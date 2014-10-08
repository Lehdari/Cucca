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


#define VISITOR(VISITOR_TYPE, COMPONENT_TYPE) class VISITOR_TYPE : public Visitor<VISITOR_TYPE, COMPONENT_TYPE>


class Node;


template<typename VisitorType_T, typename ComponentType_T>
class Visitor {
public:
    /*  CRTP Implementation of this member function will be called when a visitor
        enters a node. */
    void nodeEnter(Node* node, ComponentType_T* component) {
        static_cast<VisitorType_T*>(this)->nodeEnter(node, component);
    }

    /*  CRTP Implementation of this member function will be called when a visitor
        exits a node. */
    void nodeExit(Node* node, ComponentType_T* component) {
        static_cast<VisitorType_T*>(this)->nodeExit(node, component);
    }
};


#endif // CUCCA_CORE_VISITOR_HPP
