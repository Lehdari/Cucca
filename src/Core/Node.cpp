/**
    Cucca Game Engine - Core - Node.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-22
**/


#include "../../include/Core/Node.hpp"


using namespace Cucca;


unsigned Node::numComponentTypes__ = 0;


Node* Cucca::Node::addChild(Node&& node) {
    children_.push_back(std::unique_ptr<Node>(new Node(std::forward<Node>(node))));
    return children_.back().get();
}

std::vector<std::unique_ptr<Node>>& Cucca::Node::getChildren(void) {
    return children_;
}
