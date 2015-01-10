/**
    Cucca Game Engine - Graphics - MeshComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
**/


#include "../../include/Graphics/MeshComponent.hpp"


using namespace Cucca;


MeshComponent::MeshComponent(ResourcePointer<Mesh, ResourceId>& mesh) :
    mesh_(mesh)
{}

ResourcePointer<Mesh, ResourceId> MeshComponent::getMesh(void) {
    return mesh_;
}
