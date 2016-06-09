/**
    Cucca Game Engine - Graphics - TransformationComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#ifndef CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP
#define CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP


#include <Cucca/Core/Component.hpp>
#include <Cucca/Core/MathTypes.hpp>


namespace Cucca {

    class TransformationComponent : public Component {
    public:
        friend class TransformationVisitor;

        TransformationComponent(void);
        TransformationComponent(const Matrix4Glf& transformation);

        void setTransformation(const Matrix4Glf& transformation);
        const Matrix4Glf& getTransformation(void) const;
        const Matrix4Glf& getCumulatedTransformation(void) const;

        void translate(const Vector3Glf& to, bool absolute = false);

    private:
        Matrix4Glf transformation_;             //  relative transformation
        Matrix4Glf cumulatedTransformation_;    //  cumulated transformation
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_TRANSFORMATIONCOMPONENT_HPP


