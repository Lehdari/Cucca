#ifndef CUCCA_CORE_NODE_HPP
#define CUCCA_CORE_NODE_HPP


#include <map>
#include <vector>

#include "Visitor.hpp"


class Node {
public:
    template<typename ComponentType_T>
    void addComponent(ComponentType_T* component) {
        components_[getComponentTypeId<ComponentType_T>()].push_back(component);
    }

    template<typename ComponentType_T>
    std::vector<ComponentType_T*>& getComponents(void) {
        return components_[getComponentTypeId<ComponentType_T>()];
    }

    template<typename VisitorType_T, typename ComponentType_T>
    void visitAll(Visitor<VisitorType_T, ComponentType_T>& visitor) {
        for (auto& component : components_[getComponentTypeId<ComponentType_T>()])
            visitor.visit(static_cast<ComponentType_T*>(component));
    }

private:
    static unsigned numComponentTypes__;
    std::map<unsigned, std::vector<Component*>> components_;

    template<typename ComponentType_T>
    static unsigned getComponentTypeId(void) {
        static unsigned componentTypeId__ = numComponentTypes__++;
        return componentTypeId__;
    }
};

unsigned Node::numComponentTypes__;


#endif // CUCCA_CORE_NODE_HPP
