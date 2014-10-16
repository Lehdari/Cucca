/**
    Cucca Game Engine - Core - Node.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Node class acts as a container for user-defined components and
    basic building block for the application data structure.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-16
**/


#include "../../include/Core/Node.hpp"


void Node::addChild(Node&& node) {
    childs_.push_back(std::unique_ptr<Node>(new Node(std::forward<Node>(node))));
}

std::vector<std::unique_ptr<Node>>& Node::getChilds(void) {
    return childs_;
}
