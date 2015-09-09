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
#include "../../include/Core/MathUtils.hpp"


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
    const float segmentStepXSize = segmentXSize_ * segmentXResInv;
    const float segmentStepYSize = segmentYSize_ * segmentYResInv;

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

            float majorSample[4][4];
            sampleMajor(majorSample, (unsigned)majorSampleX, (unsigned)majorSampleY);

            /*float majorSampleXdec = majorSampleX-(unsigned)majorSampleX;
            float majorSampleYdec = majorSampleY-(unsigned)majorSampleY;
            float majorSampleX1 = majorSample[0][0] + majorSampleXdec * (majorSample[1][0] - majorSample[0][0]);
            float majorSampleX2 = majorSample[0][1] + majorSampleXdec * (majorSample[1][1] - majorSample[0][1]);
            float majorSampleInterpolated = majorSampleX1 + majorSampleYdec * (majorSampleX2 - majorSampleX1);*/
            float majorSampleDx, majorSampleDy;
            float majorSampleInterpolated = bicubicInterpolate(majorSample,
                                                               majorSampleX-(unsigned)majorSampleX,
                                                               majorSampleY-(unsigned)majorSampleY,
                                                               &majorSampleDx, &majorSampleDy);

            const float yScale = 4.0f;

            positions.push_back({ segmentStepXSize*x,
                                  majorSampleInterpolated * yScale,
                                  segmentStepYSize*y, 1.0f });
            texCoords.push_back({ sampleX, sampleY, 0.0f });
            normals.push_back({ -majorSampleDx * yScale * segmentStepYSize ,
                                segmentStepXSize * segmentStepYSize,
                                -majorSampleDy * yScale * segmentStepXSize });

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

void HeightMap::sampleMajor(float (&s)[4][4], unsigned x, unsigned y) const {
    auto majorSize = major_.getSize();
    int xx, yy;
    for (auto i=0u; i<4; ++i) {
        for (auto j=0u; j<4; ++j) {
            xx = x+i-1;
            if (xx < 0)                         xx = 0;
            if ((unsigned)xx >= majorSize.x)    xx = majorSize.x-1;
            yy = y+j-1;
            if (yy < 0)                         yy = 0;
            if ((unsigned)yy >= majorSize.y)    yy = majorSize.y-1;

            s[i][j] = major_.getPixel(xx, yy).r;
        }
    }
}
