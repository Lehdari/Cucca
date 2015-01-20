/**
    Cucca Game Engine - Graphics - Mesh.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
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
        Mesh(void);

        //  Resource init and destroy member functions
        /*
            Initialization resources:
                0: VertexData
            Dependency resources:
                0: ShaderProgram
        */
        void init(const ResourceInitInfo<Mesh>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

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

    CUCCA_RESOURCE_INIT_INFO(Mesh) { };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESH_HPP
