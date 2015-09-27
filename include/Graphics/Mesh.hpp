/**
    Cucca Game Engine - Graphics - Mesh.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#ifndef CUCCA_GRAPHICS_MESH_HPP
#define CUCCA_GRAPHICS_MESH_HPP


#include <Cucca/Core/Resource.hpp>
#include <Cucca/Core/MathTypes.hpp>
#include <Cucca/Graphics/Material.hpp>

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Mesh) {
    public:
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        Mesh(void);

        void draw(const Matrix4Glf& mvp) const;
        void draw(const Matrix4Glf& model, const Matrix4Glf& camera) const;

        void setTessellation(bool tessellated);
        bool isTessellated(void) const;

        ResourcePointer<Material, ResourceId> getMaterial(void) const;

    private:
        ResourcePointer<Material, ResourceId> material_;

        GLuint vertexArrayObjectId_;

        bool usingTexCoords_;
        bool usingNormals_;
        bool usingIndexing_;
        unsigned nIndices_;

        GLuint positionBufferId_;
        GLuint texCoordBufferId_;
        GLuint normalBufferId_;
        GLuint elementBufferId_;

        bool tessellated_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESH_HPP
