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
    template<>
    void VertexData::init<VertexDataInitInfo_HeightMap>(const VertexDataInitInfo_HeightMap& initInfo,
                                                        const std::vector<ResourceId>& initResources,
                                                        const std::vector<ResourceId>& depResources,
                                                        ResourceManager<ResourceId>* resourceManager);

    template<>
    void VertexData::destroy<VertexDataInitInfo_HeightMap>(void);

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_VERTEXDATA_INIT_HEIGHTMAP_HPP

