/**
    Cucca Game Engine - GraphicsExtensions - VertexData_Init_HeightMap.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies VertexDataInitInfo_HeightMap struct and VertexData
    init and destroy member function template specializations for
    initializing VertexData resources from a HeightMap resource.

    Initialization resources:
        0: HeightMap
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_INIT_HEIGHTMAP_HPP
#define CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_INIT_HEIGHTMAP_HPP


#include "../Core/ResourceManager.hpp"
#include "../Graphics/VertexData.hpp"
#include "HeightMap.hpp"


namespace Cucca {

    /// Initialization info struct
    struct VertexDataInitInfo_HeightMap : public ResourceInitInfoBase {
        unsigned segmentX;
        unsigned segmentY;
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(VertexData, VertexDataInitInfo_HeightMap) {

            if (initResources.size() == 0)
                return; // TODO_EXCEPTION: maybe throw an exception?

            auto heightMap = resourceManager->getResource<HeightMap>(initResources[0]);

            usingTexCoords_ = true;
            usingNormals_ = true;
            usingIndexing_ = true;

            heightMap->fillAttributeVectors(initInfo.segmentX, initInfo.segmentY,
                                            positions_, texCoords_, normals_, indices_);
    }

    CUCCA_RESOURCE_DESTROY(VertexData, VertexDataInitInfo_HeightMap) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_INIT_HEIGHTMAP_HPP

