/**
    Cucca Game Engine - Graphics - BasicCamera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#include <Cucca/Graphics/BasicCamera.hpp>
#include <Cucca/Core/Node.hpp>
#include <Cucca/Graphics/TransformationComponent.hpp>


using namespace Cucca;


void BasicCamera::nodeEnter(Node* node, MeshComponent* component) {
    //  TODO_IMPLEMENT: use dirty flag to check if transformation update is necessary
    auto transformationComponent = node->getComponents<TransformationComponent>().front();
    component->setTransformation(transformationComponent->getCumulatedTransformation());
    component->draw(projection_ * orientation_);
}

void BasicCamera::nodeExit(Node* node, MeshComponent* component) {

}
