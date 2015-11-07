/**
    Cucca Game Engine - Graphics - TransformationVisitor.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#include <Cucca/Graphics/TransformationVisitor.hpp>


using namespace Cucca;


void TransformationVisitor::nodeEnter(Node* node, TransformationComponent* component) {
    if (transformations_.size() > 0)
        transformations_.push(transformations_.top() * component->transformation_);
    else
        transformations_.push(component->transformation_);

    component->cumulatedTransformation_ = transformations_.top();
}

void TransformationVisitor::nodeExit(Node* node, TransformationComponent* component) {
    transformations_.pop();
}
