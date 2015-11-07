/**
    Cucca Game Engine - Graphics - TransformationComponent.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#include <Cucca/Graphics/TransformationComponent.hpp>


using namespace Cucca;


TransformationComponent::TransformationComponent(void) :
    transformation_(Matrix4Glf::Identity()),
    cumulatedTransformation_(Matrix4Glf::Identity())
{}

TransformationComponent::TransformationComponent(const Matrix4Glf& transformation) :
    transformation_(transformation),
    cumulatedTransformation_(transformation)
{}

void TransformationComponent::setTransformation(const Matrix4Glf& transformation) {
    transformation_ = transformation;
}

const Matrix4Glf& TransformationComponent::getTransformation(void) const {
    return transformation_;
}

const Matrix4Glf& TransformationComponent::getCumulatedTransformation(void) const {
    return cumulatedTransformation_;
}

void TransformationComponent::translate(const Vector3Glf& to, bool absolute) {
    if (absolute)
        transformation_.col(3) = (Vector4Glf() << to, 1.0f ).finished();
    else
        transformation_.col(3) += (Vector4Glf() << to, 0.0f ).finished();
}
