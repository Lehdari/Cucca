/**
    Cucca Game Engine - Graphics - Mesh.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-03-02
**/


#ifndef CUCCA_GRAPHICS_MESH_HPP
#define CUCCA_GRAPHICS_MESH_HPP


#include "../../include/Core/Resource.hpp"
#include "../../include/Core/LinearAlgebra.hpp"
#include "Material.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Mesh) {
    public:
        //  Resource init and destroy template member functions
        CUCCA_RESOURCE_INIT_DESTROY

        Mesh(void);

        void draw(const Matrix4Glf& mvp);

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
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESH_HPP
