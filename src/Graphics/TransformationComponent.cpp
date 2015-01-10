/**
    Cucca Game Engine - Graphics - TransformationComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
**/


#include "../../include/Graphics/TransformationComponent.hpp"


using namespace Cucca;


TransformationComponent::TransformationComponent(void) :
    transformation_(Matrix4Glf::Identity())
{}

TransformationComponent::TransformationComponent(const Matrix4Glf& transformation) :
    transformation_(transformation)
{}

void TransformationComponent::translate(const Vector3Glf& to, bool absolute) {
    if (absolute)
        transformation_.col(3) = (Vector4Glf() << to, 1.0f ).finished();
    else
        transformation_.col(3) += (Vector4Glf() << to, 0.0f ).finished();
}
