/**
    Cucca Game Engine - TerrainDemo - HeightMap.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#include "../include/HeightMap.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"


using namespace Cucca;


void HeightMap::fillAttributeVectors(unsigned segmentX,
                                     unsigned segmentY,
                                     std::vector<std::array<float, 4>>& positions,
                                     std::vector<std::array<float, 3>>& texCoords,
                                     std::vector<std::array<float, 3>>& normals,
                                     std::vector<unsigned>& indices,
                                     bool quads) {
    if (status() != STATUS_READY)
        return; // TODO_EXCEPTION: maybe throw an exception instead?

    auto majorSize = major_.getSize();

    positions.clear();
    texCoords.clear();
    normals.clear();
    indices.clear();

    const unsigned segmentDataSize = (segmentXResolution_+1) * (segmentYResolution_+1);
    const float segmentXResInv = 1.0f / segmentXResolution_;
    const float segmentYResInv = 1.0f / segmentYResolution_;

    positions.reserve(segmentDataSize);
    texCoords.reserve(segmentDataSize);
    normals.reserve(segmentDataSize);
    indices.reserve(segmentXResolution_ * segmentYResolution_ * 6);

    for (auto y=0u; y<=segmentYResolution_; ++y) {
        for (auto x=0u; x<=segmentXResolution_; ++x) {
            float sampleX = (segmentX + segmentXResInv*x) / numXSegments_;
            float sampleY = (segmentY + segmentYResInv*y) / numYSegments_;

            float majorSampleX = sampleX * majorSize.x;
            float majorSampleY = sampleY * majorSize.y;

            float majorSample[2][2];
            majorSample[0][0] = major_.getPixel((unsigned)majorSampleX,   (unsigned)majorSampleY  ).r;
            majorSample[1][0] = major_.getPixel((unsigned)majorSampleX+1, (unsigned)majorSampleY  ).r;
            majorSample[0][1] = major_.getPixel((unsigned)majorSampleX,   (unsigned)majorSampleY+1).r;
            majorSample[1][1] = major_.getPixel((unsigned)majorSampleX+1, (unsigned)majorSampleY+1).r;

            float majorSampleXdec = majorSampleX-(unsigned)majorSampleX;
            float majorSampleYdec = majorSampleY-(unsigned)majorSampleY;
            float majorSampleX1 = majorSample[0][0] + majorSampleXdec * (majorSample[1][0] - majorSample[0][0]);
            float majorSampleX2 = majorSample[0][1] + majorSampleXdec * (majorSample[1][1] - majorSample[0][1]);
            float majorSampleInterpolated = majorSampleX1 + majorSampleYdec * (majorSampleX2 - majorSampleX1);

            positions.push_back({ segmentXResInv*x*segmentXSize_, majorSampleInterpolated * 4.0f,
                                  segmentYResInv*y*segmentYSize_, 1.0f });
            texCoords.push_back({ sampleX, sampleY, 0.0f });
            normals.push_back({ 0.0f, 1.0f, 0.0f });

            if (x<segmentXResolution_ && y<segmentYResolution_) {
                if (quads) {
                    indices.push_back(x + (segmentXResolution_+1)*y);
                    indices.push_back(x + (segmentXResolution_+1)*y + 1);
                    indices.push_back(x + (segmentXResolution_+1)*(y+1));
                    indices.push_back(x + (segmentXResolution_+1)*(y+1) + 1);
                }
                else {
                    indices.push_back(x + (segmentXResolution_+1)*y);
                    indices.push_back(x + (segmentXResolution_+1)*(y+1));
                    indices.push_back(x + (segmentXResolution_+1)*y + 1);
                    indices.push_back(x + (segmentXResolution_+1)*y + 1);
                    indices.push_back(x + (segmentXResolution_+1)*(y+1));
                    indices.push_back(x + (segmentXResolution_+1)*(y+1) + 1);
                }
            }
        }
    }
}

unsigned HeightMap::getNumXSegments(void) const {
    return numXSegments_;
}

unsigned HeightMap::getNumYSegments(void) const {
    return numYSegments_;
}

float HeightMap::getSegmentXSize(void) const {
    return segmentXSize_;
}

float HeightMap::getSegmentYSize(void) const {
    return segmentYSize_;
}

float HeightMap::getOffsetX(void) const {
    return offsetX_;
}

float HeightMap::getOffsetY(void) const {
    return offsetY_;
}
