/**
    Cucca Game Engine - GraphicsExtensions - VertexData_Init_Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies VertexDataInitInfo_Binary struct and VertexData
    init and destroy member function template specializations for
    initializing VertexData resources representing basic shapes.

    Initialization resources:
        none
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICS_VERTEXDATA_INIT_BASICSHAPES_HPP
#define CUCCA_GRAPHICS_VERTEXDATA_INIT_BASICSHAPES_HPP


#include <Cucca/Core/ResourceManager.hpp>
#include <Cucca/Graphics/VertexData.hpp>
#include <Cucca/Core/Binary.hpp>

#include <map>
#include <cstring>


namespace Cucca {

    /// Initialization info struct
    struct VertexDataInitInfo_BasicShapes : public ResourceInitInfoBase {
        enum Shape {        //  The shape to be generated
            SHAPE_QUAD      //  a quad
        } source;

        float size;
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(VertexData, VertexDataInitInfo_BasicShapes) {
        switch (initInfo.shape) {
        case VertexDataInitInfo_BasicShapes::SHAPE_PLANE:
            {
                positions_.clear();
                texCoords_.clear();
                normals_.clear();
                indices_.clear();

                positions_.emplace_back({-initInfo.size, 0.0f, -initInfo.size});
                positions_.emplace_back({initInfo.size, 0.0f, -initInfo.size});
                positions_.emplace_back({-initInfo.size, 0.0f, initInfo.size});
                positions_.emplace_back({initInfo.size, 0.0f, initInfo.size});

                texCoords_.emplace_back({0.0f, 0.0f, 0.0f});
                texCoords_.emplace_back({1.0f, 0.0f, 0.0f});
                texCoords_.emplace_back({0.0f, 1.0f, 0.0f});
                texCoords_.emplace_back({1.0f, 1.0f, 0.0f});

                normals_.emplace_back({0.0f, 1.0f, 0.0f});
                normals_.emplace_back({0.0f, 1.0f, 0.0f});
                normals_.emplace_back({0.0f, 1.0f, 0.0f});
                normals_.emplace_back({0.0f, 1.0f, 0.0f});

                indices_.emplace_back(0);
                indices_.emplace_back(1);
                indices_.emplace_back(2);
                indices_.emplace_back(3);
            }
        break;
        }
    }

    CUCCA_RESOURCE_DESTROY(VertexData, VertexDataInitInfo_Binary) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICS_VERTEXDATA_INIT_BASICSHAPES_HPP
