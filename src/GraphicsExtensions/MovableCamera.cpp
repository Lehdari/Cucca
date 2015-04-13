/**
    Cucca Game Engine - GraphicsExtensions - MovableCamera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-15
**/


#include "../../include/GraphicsExtensions/MovableCamera.hpp"
#include "../../include/Core/Event.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream> // TEMP


using namespace Cucca;


MovableCamera::MovableCamera(void) :
    window_(nullptr),
    lockCursor_(false),
    orientation_(Matrix4Glf::Identity()),
    projection_(Matrix4Glf::Identity())
{}

MovableCamera::MovableCamera(sf::Window* window, bool lockCursor) :
    window_(window),
    lockCursor_(lockCursor),
    orientation_(Matrix4Glf::Identity()),
    projection_(Matrix4Glf::Identity())
{}

void MovableCamera::nodeEnter(Node* node, EventComponent* component) {
    auto events = component->getEvents();

    for (auto& eventBase : events) {
        if (!eventBase)
            return;

        if (eventBase->getEventType() == EventBase::getEventTypeId<sf::Event>()) {
            sf::Event* event = static_cast<Event<sf::Event>*>(eventBase.get())->getEvent();

            switch (event->type) {
            case sf::Event::MouseMoved:
            {
                std::cout << "MovableCamera mouse moved x: " << event->mouseMove.x - mouseXLast_ << ", y: " << event->mouseMove.y << std::endl;
                float xHalfAngle = atan2f((event->mouseMove.x - mouseXLast_), far_) * 0.5f;
                QuaternionGlf qx(cosf(xHalfAngle), 0.0f, sinf(xHalfAngle), 0.0f);

                QuaternionGlf q = qx;

                Matrix4Glf m;
                    m << q.matrix(), Vector3Glf(0.0f, 0.0f, 0.0f),
                         0.0f, 0.0f, 0.0f, 1.0f;

                std::cout << m << std::endl;

                orientation_ *= m;

                mouseXLast_ = event->mouseMove.x;
                mouseYLast_ = event->mouseMove.y;

                if (window_ && lockCursor_) {
                    auto ws = window_->getSize();
                    sf::Mouse::setPosition(sf::Vector2i(ws.x/2, ws.y/2), *window_);
                }
            }
            break;
            default:

            break;
            }
        }
    }

    component->clearEvents(); // TEMP make another visitor(EventClearer ?) for clearing events instead
}

void MovableCamera::nodeEnter(Node* node, TransformationComponent* component) {
    if (transformations_.size() > 0)
        transformations_.push(transformations_.top() * component->getTransformation());
    else
        transformations_.push(component->getTransformation());
}

void MovableCamera::nodeExit(Node* node, TransformationComponent* component) {
    transformations_.pop();
}

void MovableCamera::nodeEnter(Node* node, MeshComponent* component) {
    component->getMesh()->draw(projection_ * orientation_ * transformations_.top());
}

void MovableCamera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up) {
    Vector3Glf xAxis, yAxis, zAxis, t;

    zAxis = (from - to).normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    orientation_ << xAxis[0]    , xAxis[1]  , xAxis[2]  , -xAxis.dot(from),
                    yAxis[0]    , yAxis[1]  , yAxis[2]  , -yAxis.dot(from),
                    zAxis[0]    , zAxis[1]  , zAxis[2]  , -zAxis.dot(from),
                    0.0f        , 0.0f      , 0.0f      , 1.0f;

    auto w4i = 0.5f / sqrtf(1.0f + orientation_(0, 0) + orientation_(1, 1) + orientation_(2, 2));
    orientationQ_ = std::move(QuaternionGlf(0.25f*(1.0f/w4i),
                                            (orientation_(2, 1) - orientation_(1, 2))*w4i,
                                            (orientation_(0, 2) - orientation_(2, 0))*w4i,
                                            (orientation_(1, 0) - orientation_(0, 1))*w4i));
}

void MovableCamera::lookAt(Vector3Glf&& from, Vector3Glf&& to, Vector3Glf&& up) {
    lookAt(from, to, up);
}

void MovableCamera::projection(float fov, float aspectRatio, float near, float far) {
    float r = tanf(fov / 2.0f) * near;
    float t = r / aspectRatio;

    projection_ << near/r   , 0.0f      , 0.0f                  , 0.0f                      ,
                   0.0f     , near/t    , 0.0f                  , 0.0f                      ,
                   0.0f     , 0.0f      , -(far+near)/(far-near), -2.0f*far*near/(far-near) ,
                   0.0f     , 0.0f      , -1.0f                 , 0.0f                      ;

    near_ = near;
    far_ = far;
    fov_ = fov;
}
