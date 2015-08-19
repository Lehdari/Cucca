/**
    Cucca Game Engine - GraphicsExtensions - MovableCamera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-31
**/


#include "../../include/GraphicsExtensions/MovableCamera.hpp"
#include "../../include/Core/Event.hpp"

#include <SFML/Window/Event.hpp>


using namespace Cucca;


MovableCamera::MovableCamera(sf::Window* window,
                             const Matrix4Glf& orientation,
                             const Matrix4Glf& projection,
                             float near, float far, float fov,
                             const Vector3Glf& up) :
    window_(window),
    lockCursor_(false),
    cursorLockPosition_(sf::Vector2i(0, 0)),
    rotationQ_(QuaternionGlf::Identity()),
    position_(0.0f, 0.0f, 0.0f),
    orientation_(orientation),
    projection_(projection),
    near_(near),
    far_(far),
    fov_(fov),
    up_(up),
    localSpeed_(0.0f, 0.0f, 0.0f),
    localAcceleration_(0.0f, 0.0f, 0.0f),
    acceleration_(0.1f),
    maxSpeed_(1.0f),
    speedDamping_(0.9f)
{}

MovableCamera::MovableCamera(sf::Window* window, const Vector3Glf& up) :
    MovableCamera(window,
                  Matrix4Glf::Identity(), Matrix4Glf::Identity(),
                  1.0f, 100.0f, 90.0f,
                  up)
{}

void MovableCamera::nodeEnter(Node* node, EventComponent* component) {
    auto events = component->getEvents(EventBase::getEventTypeId<sf::Event>());

    for (auto& eventBase : events) {
        if (!eventBase)
            return;

        sf::Event* event = static_cast<Event<sf::Event>*>(eventBase.get())->getEvent();

        switch (event->type) {
        case sf::Event::MouseButtonPressed:
            switch (event->mouseButton.button) {
            case sf::Mouse::Right:
                lockCursor_ = true;
                cursorLockPosition_ = sf::Mouse::getPosition(*window_);
                window_->setMouseCursorVisible(false);
            break;
            default: break;
            }
        break;

        case sf::Event::MouseButtonReleased:
            switch (event->mouseButton.button) {
            case sf::Mouse::Right:
                lockCursor_ = false;
                window_->setMouseCursorVisible(true);
            break;
            default: break;
            }
        break;

        case sf::Event::MouseLeft:
            lockCursor_ = false;
            window_->setMouseCursorVisible(true);
        break;

        case sf::Event::MouseMoved:
        {
            if (window_ && lockCursor_) {
                float xHalfAngle = (event->mouseMove.x - cursorLockPosition_.x) * 0.001f;
                float yHalfAngle = (event->mouseMove.y - cursorLockPosition_.y) * 0.001f;

                QuaternionGlf qx(cosf(xHalfAngle), sinf(xHalfAngle)*up_(0), sinf(xHalfAngle)*up_(1), sinf(xHalfAngle)*up_(2));
                QuaternionGlf qy(cosf(yHalfAngle), sinf(yHalfAngle), 0.0f, 0.0f);

                rotationQ_ = qy * rotationQ_ * qx;

                sf::Mouse::setPosition(cursorLockPosition_, *window_);
            }
        }
        break;

        case sf::Event::KeyPressed:
            switch (event->key.code) {
            case sf::Keyboard::W:
                localAcceleration_(2) -= acceleration_;
            break;
            case sf::Keyboard::S:
                localAcceleration_(2) += acceleration_;
            break;
            case sf::Keyboard::A:
                localAcceleration_(0) -= acceleration_;
            break;
            case sf::Keyboard::D:
                localAcceleration_(0) += acceleration_;
            break;
            case sf::Keyboard::LShift:
                maxSpeed_ = 10.0f;
                acceleration_ *= 10.0f;
                localAcceleration_ *= 10.0f;
            break;
            default: break;
            }
        break;

        case sf::Event::KeyReleased:
            switch (event->key.code) {
            case sf::Keyboard::W:
                localAcceleration_(2) += acceleration_;
            break;
            case sf::Keyboard::S:
                localAcceleration_(2) -= acceleration_;
            break;
            case sf::Keyboard::A:
                localAcceleration_(0) += acceleration_;
            break;
            case sf::Keyboard::D:
                localAcceleration_(0) -= acceleration_;
            break;
            case sf::Keyboard::LShift:
                maxSpeed_ = 1.0f;
                acceleration_ *= 0.1f;
                localAcceleration_ *= 0.1f;
            break;
            default: break;
            }
        break;

        default: break;
        }
    }

    localSpeed_ += localAcceleration_;
    clamp(localSpeed_, -maxSpeed_, maxSpeed_);
    position_ += rotationQ_.matrix().transpose() * localSpeed_;
    localSpeed_ *= speedDamping_;

    updateOrientation();

    component->clearEvents(EventBase::getEventTypeId<sf::Event>()); // TEMP make another visitor(EventClearer ?) for clearing events instead
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
    //component->getMesh()->draw(projection_ * orientation_ * transformations_.top());
    component->getMesh()->draw(transformations_.top(), projection_ * orientation_);
}

void MovableCamera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up) {
    Vector3Glf xAxis, yAxis, zAxis, t;

    zAxis = (from - to).normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    auto w4i = 0.5f / sqrtf(1.0f + xAxis(0) + yAxis(1) + zAxis(2));
    rotationQ_ = std::move(QuaternionGlf(0.25f*(1.0f/w4i),
                                         (yAxis(2) - zAxis(1))*w4i,
                                         (zAxis(0) - xAxis(2))*w4i,
                                         (xAxis(1) - yAxis(0))*w4i));
    position_ = from;

    updateOrientation();

    up_ = up;
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

const Vector3Glf& MovableCamera::getPosition(void) const {
    return position_;
}

void MovableCamera::updateOrientation(void) {
    orientation_ << rotationQ_.matrix(), rotationQ_.matrix() * -position_,
                    0.0f, 0.0f, 0.0f, 1.0f;
}
