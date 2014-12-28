/**
    Cucca Game Engine - Core - Visitor.hpp


    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    Visitor class defines a CRTP interface for manipulating components
    of nodes. CRTP calls will be made through VisitorInterface class.

    Create custom visitor by deriving from Visitor class or by using the
    macro provided and implementing nodeEnter and nodeExit member
    functions for all the component types you wish to gain access to.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-28
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
        void nodeEnter(Node* node, FirstComponentType_T* component) {
            static_cast<VisitorType_T*>(this)->nodeEnter(node, component);
        }

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
