/**
    Cucca Game Engine - Core - Node.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Node class acts as a container for user-defined components and
    basic building block for the application data structure.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-28
**/


#ifndef CUCCA_CORE_NODE_HPP
#define CUCCA_CORE_NODE_HPP


#include "Component.hpp"
#include "Visitor.hpp"

#include <unordered_map>
#include <vector>
#include <memory>
#include <utility>


namespace Cucca {

    class Node {
    public:
        //  Add new component (uses move semantics)
        template<typename ComponentType_T>
        void addComponent(ComponentType_T&& component);

        //  Get vector of given type of components the node contains
        template<typename ComponentType_T>
        std::vector<ComponentType_T*> getComponents(void);

        /*  Accept a visitor. Visitor will visit every component of given type in
            the node and its childs in hierarchical order. */
        template<typename VisitorType_T, typename ...ComponentTypes_T>
        void accept(Visitor<VisitorType_T, ComponentTypes_T...>& visitor);

        //  Add a child node (uses move semantics)
        void addChild(Node&& node);

        //  Get reference to a vector of childs of the node
        std::vector<std::unique_ptr<Node>>& getChilds(void);

    private:
        /*  Component type information system. For every new component type, an
            unique identifier will be created in compile-time. */
        static unsigned numComponentTypes__;

        template<typename ComponentType_T>
        static unsigned getComponentTypeId(void) {
            static unsigned componentTypeId__ = numComponentTypes__++;
            return componentTypeId__;
        }

        //  Component/child pointer data
        std::unordered_map<unsigned, std::vector<std::unique_ptr<Component>>> components_;
        std::vector<std::unique_ptr<Node>> childs_;

        template<typename VisitorType_T, typename FirstComponentType_T, typename ...RestComponentTypes_T>
        void nodeEnterRecursive(VisitorInterface<VisitorType_T, FirstComponentType_T, RestComponentTypes_T...>& visitor);

        template<typename VisitorType_T, typename FirstComponentType_T, typename ...RestComponentTypes_T>
        void nodeExitRecursive(VisitorInterface<VisitorType_T, FirstComponentType_T, RestComponentTypes_T...>& visitor);

        template<typename VisitorType_T>
        void nodeEnterRecursive(VisitorInterface<VisitorType_T>& visitor) {}

        template<typename VisitorType_T>
        void nodeExitRecursive(VisitorInterface<VisitorType_T>& visitor) {}
    };


    //  Member definitions
    template<typename ComponentType_T>
    void Node::addComponent(ComponentType_T&& component) {
        components_[getComponentTypeId<ComponentType_T>()].push_back(std::unique_ptr<Component>(new ComponentType_T(std::forward<ComponentType_T>(component))));
    }

    template<typename ComponentType_T>
    std::vector<ComponentType_T*> Node::getComponents(void) {
        unsigned typeId = getComponentTypeId<ComponentType_T>();
        std::vector<ComponentType_T*> components(components_[typeId]);
        for (auto& component : components_[typeId])
            components.push_back(static_cast<ComponentType_T*>(component.get()));
        return components;
    }

    template<typename VisitorType_T, typename ...ComponentTypes_T>
    void Node::accept(Visitor<VisitorType_T, ComponentTypes_T...>& visitor) {
        nodeEnterRecursive(*static_cast<VisitorInterface<VisitorType_T, ComponentTypes_T...>*>(&visitor));

        for (auto& child : childs_)
            child->accept(visitor);

        nodeExitRecursive(*static_cast<VisitorInterface<VisitorType_T, ComponentTypes_T...>*>(&visitor));
    }

    template<typename VisitorType_T, typename FirstComponentType_T, typename ...RestComponentTypes_T>
    void Node::nodeEnterRecursive(VisitorInterface<VisitorType_T, FirstComponentType_T, RestComponentTypes_T...>& visitor) {
        auto& componentVector = components_[getComponentTypeId<FirstComponentType_T>()];

        for (auto it = componentVector.begin(); it != componentVector.end(); ++it)
            visitor.nodeEnter(this, static_cast<FirstComponentType_T*>(it->get()));

        nodeEnterRecursive(*static_cast<VisitorInterface<VisitorType_T, RestComponentTypes_T...>*>(&visitor));
    }

    template<typename VisitorType_T, typename FirstComponentType_T, typename ...RestComponentTypes_T>
    void Node::nodeExitRecursive(VisitorInterface<VisitorType_T, FirstComponentType_T, RestComponentTypes_T...>& visitor) {
        auto& componentVector = components_[getComponentTypeId<FirstComponentType_T>()];

        nodeExitRecursive(*static_cast<VisitorInterface<VisitorType_T, RestComponentTypes_T...>*>(&visitor));

        for (auto it = componentVector.cbegin(); it != componentVector.cend(); ++it)
            visitor.nodeExit(this, static_cast<FirstComponentType_T*>(it->get()));
    }

} // namespace Cucca


#endif // CUCCA_CORE_NODE_HPP
