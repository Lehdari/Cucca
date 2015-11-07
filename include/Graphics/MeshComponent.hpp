/**
    Cucca Game Engine - Graphics - MeshComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-11-07
**/


#ifndef CUCCA_GRAPHICS_MESHCOMPONENT_HPP
#define CUCCA_GRAPHICS_MESHCOMPONENT_HPP


#include <Cucca/Core/Component.hpp>
#include <Cucca/Graphics/Mesh.hpp>
#include <Cucca/Core/MathTypes.hpp>


namespace Cucca {

    class MeshComponent : public Component {
    public:
        MeshComponent(ResourcePointer<Mesh, ResourceId>& mesh,
                      const Matrix4Glf& transformation = Matrix4Glf::Identity());

        const Mesh& getMesh(void) const;
        ResourcePointer<Mesh, ResourceId> getMeshPointer(void) const;

        void setTransformation(const Matrix4Glf& transformation);
        void draw(const Matrix4Glf& camera) const;

    private:
        ResourcePointer<Mesh, ResourceId> mesh_;
        Matrix4Glf transformation_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESHCOMPONENT_HPP

