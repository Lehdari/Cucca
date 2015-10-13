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


#include <Cucca/Core/Visitor.hpp>
#include <Cucca/Graphics/Camera.hpp>
#include <Cucca/Core/EventComponent.hpp>
#include <Cucca/Graphics/TransformationComponent.hpp>
#include <Cucca/Graphics/MeshComponent.hpp>
#include <Cucca/Core/MathTypes.hpp>

#include <stack>
#include <SFML/Window.hpp>


namespace Cucca {

    CUCCA_VISITOR(MovableCamera, EventComponent, TransformationComponent, MeshComponent), public Camera {
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

        std::stack<Matrix4Glf> transformations_;

        Vector3Glf localSpeed_; // local axis(rotated) speed
        Vector3Glf localAcceleration_; // local axis acceleration
        float acceleration_; // value the acceleration is set to when key is pressed
        float maxSpeed_;
        float speedDamping_; // speed damping (must lie in range [0,1) )
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_MOVABLECAMERA_HPP
