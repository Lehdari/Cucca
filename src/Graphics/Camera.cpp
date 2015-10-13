/**
    Cucca Game Engine - Graphics - Camera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-10-11
**/


#include <Cucca/Graphics/Camera.hpp>


using namespace Cucca;


Camera::Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               float fov, float aspectRatio, float near, float far) :
    position_(position), forward_(forward), up_(up),
    fov_(fov), aspectRatio_(aspectRatio), near_(near), far_(far),
    rotationQ_(QuaternionGlf::Identity()),
    orientation_(Matrix4Glf::Identity()),
    projection_(Matrix4Glf::Identity())
{}

Camera::Camera(void) :
    Camera(Vector3Glf(0.0f, 0.0f, 0.0f), Vector3Glf(0.0f, 0.0f, -1.0f), Vector3Glf(0.0f, 1.0f, 0.0f),
           PI*0.5f, 4.0f/3.0f, 0.1f, 1000.0f)
{}

/*
void Camera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up) {
    Vector3Glf xAxis, yAxis, zAxis;

    zAxis = (to - from).normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    orientation_ << xAxis[0]    , xAxis[1]  , xAxis[2]  , -xAxis.dot(from),
                    yAxis[0]    , yAxis[1]  , yAxis[2]  , -yAxis.dot(from),
                    -zAxis[0]   , -zAxis[1] , -zAxis[2] , zAxis.dot(from) ,
                    0.0f        , 0.0f      , 0.0f      , 1.0f;
}*/

//  TODO FIX fix this function to produce equal results to the one above
void Camera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up) {
    position_ = from;
    forward_ = to - from;
    up_ = up;

    Vector3Glf xAxis, yAxis, zAxis, t;

    zAxis = -forward_.normalized();
    xAxis = up_.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    auto w4i = 0.5f / sqrtf(1.0f + xAxis(0) + yAxis(1) + zAxis(2));
    rotationQ_ = std::move(QuaternionGlf(0.25f*(1.0f/w4i),
                                         (yAxis(2) - zAxis(1))*w4i,
                                         (zAxis(0) - xAxis(2))*w4i,
                                         (xAxis(1) - yAxis(0))*w4i));

    updateOrientation();
}

void Camera::lookAt(Vector3Glf&& from, Vector3Glf&& to, Vector3Glf&& up) {
    lookAt(from, to, up);
}

void Camera::projection(float fov, float aspectRatio, float near, float far) {
    float r = tanf(fov / 2.0f) * near;
    float t = r / aspectRatio;

    projection_ << near/r   , 0.0f      , 0.0f                  , 0.0f                      ,
                   0.0f     , near/t    , 0.0f                  , 0.0f                      ,
                   0.0f     , 0.0f      , -(far+near)/(far-near), -2.0f*far*near/(far-near) ,
                   0.0f     , 0.0f      , -1.0f                 , 0.0f                      ;
}

const Vector3Glf& Camera::getPosition(void) const {
    return position_;
}

void Camera::updateOrientation(void) {
    auto rotationMatrix = rotationQ_.matrix();
    orientation_ << rotationMatrix, rotationMatrix * -position_,
                    0.0f, 0.0f, 0.0f, 1.0f;
}
