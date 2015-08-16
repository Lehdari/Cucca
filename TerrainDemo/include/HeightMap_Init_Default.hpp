/**
    Cucca Game Engine - TerrainDemo - HeightMap_Init_Default.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies HeightMapInitInfo_Default struct and HeightMap init
    and destroy member function template specializations for initializing
    HeightMap resources.

    Initialization resources:
        0: Binary (major texture)
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-21
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_INIT_DEFAULT_HPP
#define CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_INIT_DEFAULT_HPP


#include "HeightMap.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"


namespace Cucca {

    /// Initialization info struct
    struct HeightMapInitInfo_Default : public ResourceInitInfoBase {
        unsigned numXSegments;
        unsigned numYSegments;
        unsigned segmentXResolution;
        unsigned segmentYResolution;
        float segmentXSize;
        float segmentYSize;
        float offsetX;
        float offsetY;
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(HeightMap, HeightMapInitInfo_Default) {
        if (initResources.size() < 1)
            return; // TODO_EXCEPTION: maybe throw a proper exception instead?

        numXSegments_ = initInfo.numXSegments;
        numYSegments_ = initInfo.numYSegments;
        segmentXResolution_ = initInfo.segmentXResolution;
        segmentYResolution_ = initInfo.segmentYResolution;
        segmentXSize_ = initInfo.segmentXSize;
        segmentYSize_ = initInfo.segmentYSize;
        offsetX_ = initInfo.offsetX;
        offsetY_ = initInfo.offsetY;

        auto majorBinary = resourceManager->getResource<Binary>(initResources[0]);

        major_.loadFromMemory(majorBinary->getBufferPtr(), majorBinary->getBufferSize());
    }

    CUCCA_RESOURCE_DESTROY(HeightMap, HeightMapInitInfo_Default) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_INIT_DEFAULT_HPP
