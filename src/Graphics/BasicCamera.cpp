/**
    Cucca Game Engine - Graphics - BasicCamera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-10-11
**/


#include <Cucca/Graphics/BasicCamera.hpp>


using namespace Cucca;


/*BasicCamera::BasicCamera(void) :
    orientation_(Matrix4Glf::Identity()),
    projection_(Matrix4Glf::Identity())
{}*/

void BasicCamera::nodeEnter(Node* node, TransformationComponent* component) {
    if (transformations_.size() > 0)
        transformations_.push(transformations_.top() * component->transformation_);
    else
        transformations_.push(component->transformation_);
}

void BasicCamera::nodeExit(Node* node, TransformationComponent* component) {
    transformations_.pop();
}

void BasicCamera::nodeEnter(Node* node, MeshComponent* component) {
    component->mesh_->draw(projection_ * orientation_ * transformations_.top());
}

void BasicCamera::nodeExit(Node* node, MeshComponent* component) {

}
