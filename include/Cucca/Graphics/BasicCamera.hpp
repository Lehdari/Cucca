/**
    Cucca Game Engine - Graphics - BasicCamera.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#ifndef CUCCA_GRAPHICS_BASICCAMERA_HPP
#define CUCCA_GRAPHICS_BASICCAMERA_HPP


#include <Cucca/Core/Visitor.hpp>
#include <Cucca/Graphics/Camera.hpp>
#include <Cucca/Graphics/MeshComponent.hpp>
#include <Cucca/Core/MathTypes.hpp>

#include <stack>


namespace Cucca {

    CUCCA_VISITOR(BasicCamera, MeshComponent), public Camera {
    public:
        void nodeEnter(Node* node, MeshComponent* component);
        void nodeExit(Node* node, MeshComponent* component);
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_BASICCAMERA_HPP
