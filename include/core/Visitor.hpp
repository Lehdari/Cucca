#ifndef CUCCA_CORE_VISITOR_HPP
#define CUCCA_CORE_VISITOR_HPP


#include "Component.hpp"


#define VISIT(COMPONENT_TYPE) template<>\
void Visitor<COMPONENT_TYPE>::visit(COMPONENT_TYPE* component)


template<typename ComponentType_T>
class Visitor {
public:
    friend class Node;

private:
    static void visit(ComponentType_T* component);

    static void castVisit(ComponentBase* component) {
        visit(static_cast<ComponentType_T*>(component));
    }
};


#endif // CUCCA_CORE_VISITOR_HPP
