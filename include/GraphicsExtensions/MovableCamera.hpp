/**
    Cucca Game Engine - GraphicsExtensions - MovableCamera.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-31
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_MOVABLECAMERA_HPP
#define CUCCA_GRAPHICSEXTENSIONS_MOVABLECAMERA_HPP


#include "../Core/Visitor.hpp"
#include "../Core/EventComponent.hpp"
#include "../Graphics/TransformationComponent.hpp"
#include "../Graphics/MeshComponent.hpp"
#include "../Core/LinearAlgebra.hpp"

#include <stack>
#include <SFML/Window.hpp>


namespace Cucca {

    CUCCA_VISITOR(MovableCamera, EventComponent, TransformationComponent, MeshComponent) {
    public:
        MovableCamera(sf::Window* window = nullptr,
                      const Matrix4Glf& orientation = Matrix4Glf::Identity(),
                      const Matrix4Glf& projection = Matrix4Glf::Identity(),
                      float near = 1.0f, float far = 100.0f, float fov = 90.0f,
                      const Vector3Glf& up = Vector3Glf(0.0f, 1.0f, 0.0f));
        MovableCamera(sf::Window* window, const Vector3Glf& up);

        void nodeEnter(Node* node, EventComponent* component);
        void nodeExit(Node* node, EventComponent* component) {}
        void nodeEnter(Node* node, TransformationComponent* component);
        void nodeExit(Node* node, TransformationComponent* component);
        void nodeEnter(Node* node, MeshComponent* component);
        void nodeExit(Node* node, MeshComponent* component) {}

        void lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up);
        void lookAt(Vector3Glf&& from, Vector3Glf&& to, Vector3Glf&& up);
        void projection(float fov, float aspectRatio, float near, float far);

        const Vector3Glf& getPosition(void) const;

    private:
        sf::Window* window_;

        bool lockCursor_;
        sf::Vector2i cursorLockPosition_;

        QuaternionGlf rotationQ_;
        Vector3Glf position_;

        Matrix4Glf orientation_; // formed using rotationQ_ and position_(see updateOrientation member function)
        Matrix4Glf projection_;
        float near_;
        float far_;
        float fov_;
        Vector3Glf up_;

        std::stack<Matrix4Glf> transformations_;

        Vector3Glf localSpeed_; // local axis(rotated) speed
        Vector3Glf localAcceleration_; // local axis acceleration
        float acceleration_; // value the acceleration is set to when key is pressed
        float maxSpeed_;
        float speedDamping_; // speed damping (must lie in range [0,1) )

        void updateOrientation(void);
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_MOVABLECAMERA_HPP
