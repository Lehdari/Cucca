/**
    Cucca Game Engine - Graphics - MeshComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#include <Cucca/Graphics/MeshComponent.hpp>


using namespace Cucca;


MeshComponent::MeshComponent(ResourcePointer<Mesh, ResourceId>& mesh,
                             const Matrix4Glf& transformation) :
    mesh_(mesh),
    transformation_(transformation)
{}

const Mesh& MeshComponent::getMesh(void) const {
    return *mesh_;
}

ResourcePointer<Mesh, ResourceId> MeshComponent::getMeshPointer(void) const {
    return mesh_;
}

void MeshComponent::setTransformation(const Matrix4Glf& transformation) {
    transformation_ = transformation;
}

void MeshComponent::draw(const Matrix4Glf& camera) const {
    mesh_->draw(transformation_, camera);
}
