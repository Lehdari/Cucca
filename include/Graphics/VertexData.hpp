/**
    Cucca Game Engine - Core - VertexData.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-08
**/


#ifndef CUCCA_GRAPHICS_VERTEXDATA_HPP
#define CUCCA_GRAPHICS_VERTEXDATA_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    //  Resource
    CUCCA_RESOURCE(VertexData) {
    public:
        VertexData(void);

        //  Resource init and destroy member functions
        /*
            Initialization resources:
                0: .obj file binary
        */
        void init(const ResourceInitInfo<VertexData>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        bool usesTextureCoordinates(void) const;
        bool usesNormals(void) const;
        bool usesIndexing(void) const;

        const std::vector<std::array<float, 4>>& getPositions(void) const;
        const std::vector<std::array<float, 3>>& getTextureCoordinates(void) const;
        const std::vector<std::array<float, 3>>& getNormals(void) const;
        const std::vector<unsigned>& getIndices(void) const;

    private:
        bool usingTexCoords_;
        bool usingNormals_;
        bool usingIndexing_;

        std::vector<std::array<float, 4>> positions_;
        std::vector<std::array<float, 3>> texCoords_;
        std::vector<std::array<float, 3>> normals_;
        std::vector<unsigned> indices_;
    };


    //  Initialization info
    CUCCA_RESOURCE_INIT_INFO(VertexData) {
        enum Source {
            SOURCE_BINARY_OBJ,      //  from .obj file
            SOURCE_HEIGHTMAP        //  from HeightMap resource
        } source;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_VERTEXDATA_HPP
