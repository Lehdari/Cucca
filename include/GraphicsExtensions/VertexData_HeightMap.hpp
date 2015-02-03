/**
    Cucca Game Engine - GraphicsExtensions - VertexData_Binary.hpp

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


#ifndef CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_HEIGHTMAP_HPP
#define CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_HEIGHTMAP_HPP


#include "../Core/ResourceManager.hpp"
#include "../Graphics/VertexData.hpp"
#include "HeightMap.hpp"


namespace Cucca {

    /// Initialization info struct
    struct VertexDataInitInfo_HeightMap : public ResourceInitInfoBase { };


    /// Resource init and destroy template member function specializations
    template<>
    void VertexData::init<VertexDataInitInfo_HeightMap>(const VertexDataInitInfo_HeightMap& initInfo,
                                                        const std::vector<ResourceId>& initResources,
                                                        const std::vector<ResourceId>& depResources,
                                                        ResourceManager<ResourceId>* resourceManager) {

            if (initResources.size() == 0)
                return; // TODO_EXCEPTION: maybe throw an exception?

            auto heightMap = resourceManager->getResource<HeightMap>(initResources[0]);

            usingTexCoords_ = true;
            usingNormals_ = true;
            usingIndexing_ = true;

            heightMap->fillAttributeVectors(positions_, texCoords_, normals_, indices_);
    }

    template<>
    void VertexData::destroy<VertexDataInitInfo_HeightMap>(void) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_HEIGHTMAP_HPP

