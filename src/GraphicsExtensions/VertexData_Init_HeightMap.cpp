/**
    Cucca Game Engine - GraphicsExtensions - VertexData_Init_HeightMap.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#include "../../include/GraphicsExtensions/VertexData_Init_HeightMap.hpp"


using namespace Cucca;


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

        heightMap->fillAttributeVectors(initInfo.segmentX, initInfo.segmentY,
                                        positions_, texCoords_, normals_, indices_);
}

template<>
void VertexData::destroy<VertexDataInitInfo_HeightMap>(void) {}
