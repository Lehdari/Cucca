/**
    Cucca Game Engine - Core - Node.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Node class acts as a container for user-defined components and
    basic building block for the application data structure.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-17
**/


#ifndef CUCCA_CORE_NODE_HPP
#define CUCCA_CORE_NODE_HPP


#include "Component.hpp"
#include "Visitor.hpp"

#include <map>
#include <vector>
#include <memory>
#include <utility>


namespace Cucca {
    class Node {
    public:
        //  Add new component (uses move semantics)
        template<typename ComponentType_T>
        void addComponent(ComponentType_T&& component) {
            components_[getComponentTypeId<ComponentType_T>()].push_back(std::unique_ptr<Component>(new ComponentType_T(std::forward<ComponentType_T>(component))));
        }


        //  Get vector of given type of components the node contains
        template<typename ComponentType_T>
        std::vector<ComponentType_T*> getComponents(void) {
            std::vector<ComponentType_T*> components;
            for (auto& component : components_[getComponentTypeId<ComponentType_T>()])
                components.push_back(static_cast<ComponentType_T*>(component.get()));
            return components;
        }

        /*  Accept a visitor. Visitor will visit every component of given type in
            the node and its childs in hierarchical order. */
        template<typename VisitorType_T, typename ComponentType_T>
        void accept(Visitor<VisitorType_T, ComponentType_T>& visitor) {
            auto& componentVector = components_[getComponentTypeId<ComponentType_T>()];

            for (auto it = componentVector.begin(); it != componentVector.end(); ++it)
                visitor.nodeEnter(this, static_cast<ComponentType_T*>(it->get()));

            for (auto& child : childs_)
                child->accept(visitor);

            for (auto it = componentVector.rbegin(); it != componentVector.rend(); ++it)
                visitor.nodeExit(this, static_cast<ComponentType_T*>(it->get()));
        }

        //  Add a child node (uses move semantics)
        void addChild(Node&& node);

        //  Get reference to a vector of childs of the node
        std::vector<std::unique_ptr<Node>>& getChilds(void);

    private:
        /*  Component type information system. For every new component type, an
            unique identifier will be created in compile-time. */
        template<typename ComponentType_T>
        static unsigned getComponentTypeId(void) {
            static unsigned numComponentTypes__;
            static unsigned componentTypeId__ = numComponentTypes__++;
            return componentTypeId__;
        }

        //  Component/child pointer data
        std::map<unsigned, std::vector<std::unique_ptr<Component>>> components_;
        std::vector<std::unique_ptr<Node>> childs_;
    };
}


#endif // CUCCA_CORE_NODE_HPP
