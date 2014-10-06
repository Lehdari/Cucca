#ifndef CUCCA_CORE_VISITOR_HPP
#define CUCCA_CORE_VISITOR_HPP


#define VISITOR(VISITOR_TYPE, COMPONENT_TYPE) class VISITOR_TYPE : public Visitor<VISITOR_TYPE, COMPONENT_TYPE>


class Node;


template<typename VisitorType_T, typename ComponentType_T>
class Visitor {
public:
    void nodeEnter(Node* node, ComponentType_T* component) {
        static_cast<VisitorType_T*>(this)->nodeEnter(node, component);
    }

    void nodeExit(Node* node, ComponentType_T* component) {
        static_cast<VisitorType_T*>(this)->nodeExit(node, component);
    }
};


#endif // CUCCA_CORE_VISITOR_HPP
