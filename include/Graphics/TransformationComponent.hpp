/**
    Cucca Game Engine - Graphics - TransformationComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-01-10
**/


#ifndef CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP
#define CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP


#include "../Core/Component.hpp"
#include "../Core/LinearAlgebra.hpp"


namespace Cucca {

    class TransformationComponent : public Component {
    public:

    private:
        Matrix4Glf transformation_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP


