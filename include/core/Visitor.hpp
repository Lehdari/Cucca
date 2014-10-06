#ifndef CUCCA_CORE_VISITOR_HPP
#define CUCCA_CORE_VISITOR_HPP


#define VISITOR(VISITOR_TYPE, COMPONENT_TYPE) class VISITOR_TYPE : public Visitor<VISITOR_TYPE, COMPONENT_TYPE>

template<typename VisitorType_T, typename ComponentType_T>
class Visitor {
public:
    void visit(ComponentType_T* component) {
        static_cast<VisitorType_T*>(this)->visit(component);
    }
};


#endif // CUCCA_CORE_VISITOR_HPP
