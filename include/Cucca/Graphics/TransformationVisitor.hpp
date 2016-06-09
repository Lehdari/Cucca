/**
    Cucca Game Engine - Graphics - TransformationVisitor.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#ifndef CUCCA_GRAPHICS_TRANSFORMATIONVISITOR_HPP
#define CUCCA_GRAPHICS_TRANSFORMATIONVISITOR_HPP


#include <Cucca/Core/Visitor.hpp>
#include <Cucca/Graphics/TransformationComponent.hpp>
#include <Cucca/Core/MathTypes.hpp>

#include <stack>


namespace Cucca {

    CUCCA_VISITOR(TransformationVisitor, TransformationComponent) {
    public:
        void nodeEnter(Node* node, TransformationComponent* component);
        void nodeExit(Node* node, TransformationComponent* component);

    private:
        std::stack<Matrix4Glf> transformations_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_TRANSFORMATIONVISITOR_HPP

