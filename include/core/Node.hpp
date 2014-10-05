#ifndef CUCCA_CORE_NODE_HPP
#define CUCCA_CORE_NODE_HPP


#include <map>
#include <vector>
#include <iostream>

#include "Visitor.hpp"


class Node {
public:
    template<typename ComponentType_T>
    void addComponent(ComponentType_T* component) {
        std::cout << sizeof(ComponentVisit) << std::endl;
        components_[&Visitor<ComponentType_T>::castVisit].push_back(component);
    }

    template<typename ComponentType_T>
    std::vector<ComponentType_T*>& getComponents(void) {
        return components_[&Visitor<ComponentType_T>::castVisit];
    }

    template<typename ComponentType_T>
    void visitAll(void) {
        for (auto& component : components_[&Visitor<ComponentType_T>::castVisit])
            Visitor<ComponentType_T>::castVisit(component);
    }

private:
    typedef void (*ComponentVisit)(ComponentBase*);
    std::map<ComponentVisit, std::vector<ComponentBase*>> components_;
};


#endif // CUCCA_CORE_NODE_HPP
