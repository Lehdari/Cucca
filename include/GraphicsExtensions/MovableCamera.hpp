/**
    Cucca Game Engine - GraphicsExtensions - MovableCamera.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-15
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
        MovableCamera(void);
        MovableCamera(sf::Window* window, bool lockCursor = true);

        void nodeEnter(Node* node, EventComponent* component);
        void nodeExit(Node* node, EventComponent* component) {}
        void nodeEnter(Node* node, TransformationComponent* component);
        void nodeExit(Node* node, TransformationComponent* component);
        void nodeEnter(Node* node, MeshComponent* component);
        void nodeExit(Node* node, MeshComponent* component) {}

        void lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up);
        void lookAt(Vector3Glf&& from, Vector3Glf&& to, Vector3Glf&& up);
        void projection(float fov, float aspectRatio, float near, float far);

    private:
        sf::Window* window_;
        bool lockCursor_;

        QuaternionGlf orientationQ_;

        Matrix4Glf orientation_;
        Matrix4Glf projection_;
        float near_;
        float far_;
        float fov_;

        std::stack<Matrix4Glf> transformations_;

        int mouseXLast_;
        int mouseYLast_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_MOVABLECAMERA_HPP
