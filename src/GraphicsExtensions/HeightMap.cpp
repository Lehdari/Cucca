/**
    Cucca Game Engine - GraphicsExtensions - HeightMap.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-25
**/


#include "../../include/GraphicsExtensions/HeightMap.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"


using namespace Cucca;


void HeightMap::fillAttributeVectors(std::vector<std::array<float, 4>>& positions,
                                     std::vector<std::array<float, 3>>& texCoords,
                                     std::vector<std::array<float, 3>>& normals,
                                     std::vector<unsigned>& indices) {
    if (status() != STATUS_READY)
        return; // TODO_EXCEPTION: maybe throw an exception instead?

    auto majorSize = major_.getSize();

    positions.clear();
    texCoords.clear();
    normals.clear();
    indices.clear();

    positions.reserve(majorSize.x * majorSize.y);
    texCoords.reserve(majorSize.x * majorSize.y);
    normals.reserve(majorSize.x * majorSize.y);
    indices.reserve((majorSize.x-1) * (majorSize.y-1) * 6);

    for (auto y=0u; y<majorSize.y; ++y) {
        for (auto x=0u; x<majorSize.x; ++x) {
            auto pix = major_.getPixel(x, y);
            positions.push_back({ (float)x, pix.r/5.0f, (float)y, 1.0f});
            texCoords.push_back({ x/(float)majorSize.x, y/(float)majorSize.y, 0.0f });
            normals.push_back({ 0.0f, 1.0f, 0.0f });

            if (x<majorSize.x-1 && y<majorSize.y-1) {
                indices.push_back(x + majorSize.x*y);
                indices.push_back(x + majorSize.x*(y+1));
                indices.push_back(x + majorSize.x*y + 1);
                indices.push_back(x + majorSize.x*y + 1);
                indices.push_back(x + majorSize.x*(y+1));
                indices.push_back(x + majorSize.x*(y+1) + 1);
            }
        }
    }
}
