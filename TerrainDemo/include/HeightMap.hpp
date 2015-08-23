/**
    Cucca Game Engine - TerrainDemo - HeightMap.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP
#define CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP


#include "../../include/Core/Resource.hpp"

#include <SFML/Graphics/Image.hpp>


namespace Cucca {

    //  Resource
    CUCCA_RESOURCE(HeightMap) {
    public:
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        void fillAttributeVectors(unsigned segmentX,
                                  unsigned segmentY,
                                  std::vector<std::array<float, 4>>& positions,
                                  std::vector<std::array<float, 3>>& texCoords,
                                  std::vector<std::array<float, 3>>& normals,
                                  std::vector<unsigned>& indices,
                                  bool quads = true);

        unsigned getNumXSegments(void) const;
        unsigned getNumYSegments(void) const;
        float getSegmentXSize(void) const;
        float getSegmentYSize(void) const;
        float getOffsetX(void) const;
        float getOffsetY(void) const;

    private:
        sf::Image major_;
        unsigned numXSegments_;
        unsigned numYSegments_;
        unsigned segmentXResolution_;
        unsigned segmentYResolution_;
        float segmentXSize_;
        float segmentYSize_;
        float offsetX_;
        float offsetY_;

        void sampleMajor(float (&s)[4][4], unsigned x, unsigned y) const;
    };

}; // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP
