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
    void accept(Visitor<VisitorType_T, ComponentType_T>& visitor) {
        auto& componentVector = components_[getComponentTypeId<ComponentType_T>()];

        for (auto it = componentVector.begin(); it != componentVector.end(); ++it)
            visitor.nodeEnter(this, static_cast<ComponentType_T*>(*it));

        for (auto& child : childs_)
            child->accept(visitor);

        for (auto it = componentVector.rbegin(); it != componentVector.rend(); ++it)
            visitor.nodeExit(this, static_cast<ComponentType_T*>(*it));
    }

    void addChild(Node* node) {
        childs_.push_back(node);
    }

    void addChild(Node& node) {
        childs_.push_back(&node);
    }

private:
    static unsigned numComponentTypes__;
    std::map<unsigned, std::vector<Component*>> components_;
    std::vector<Node*> childs_;

    template<typename ComponentType_T>
    static unsigned getComponentTypeId(void) {
        static unsigned componentTypeId__ = numComponentTypes__++;
        return componentTypeId__;
    }
};

unsigned Node::numComponentTypes__;


#endif // CUCCA_CORE_NODE_HPP
