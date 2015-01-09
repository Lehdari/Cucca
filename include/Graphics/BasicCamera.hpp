/**
    Cucca Game Engine - Graphics - BasicCamera.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-09
**/


#ifndef CUCCA_GRAPHICS_BASICCAMERA_HPP
#define CUCCA_GRAPHICS_BASICCAMERA_HPP


#include "../../include/Core/Visitor.hpp"
#include "../../include/Graphics/MeshComponent.hpp"
#include "../../include/Core/LinearAlgebra.hpp"


namespace Cucca {

    CUCCA_VISITOR(BasicCamera, MeshComponent) {
    public:
        BasicCamera(void);

        void nodeEnter(Node* node, MeshComponent* component);
        void nodeExit(Node* node, MeshComponent* component);

    private:
        GlMatrix4f orientation_;
        GlMatrix4f perspective_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_BASICCAMERA_HPP
