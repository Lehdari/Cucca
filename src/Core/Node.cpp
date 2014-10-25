/**
    Cucca Game Engine - Core - Node.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-10-16
**/


#include "../../include/Core/Node.hpp"


using namespace Cucca;


void Cucca::Node::addChild(Node&& node) {
    childs_.push_back(std::unique_ptr<Node>(new Node(std::forward<Node>(node))));
}

std::vector<std::unique_ptr<Node>>& Cucca::Node::getChilds(void) {
    return childs_;
}
