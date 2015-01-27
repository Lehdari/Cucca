/**
    Cucca Game Engine - GraphicsExtensions - HeightMap.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-25
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP
#define CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP


#include "../../include/Core/Resource.hpp"

// TODO_IMPLEMENT: provide a proper level of abstraction between Cucca and external libraries
#include <SFML/Graphics/Image.hpp> // TEMP


namespace Cucca {

    //  Resource
    CUCCA_RESOURCE(HeightMap) {
    public:
        //  Resource init and destroy member functions
        /*
            Initialization resources:
                0: Major texture (Binary[image file])
        */
        void init(const ResourceInitInfo<HeightMap>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void) {}

        void fillAttributeVectors(std::vector<std::array<float, 4>>& positions,
                                  std::vector<std::array<float, 3>>& texCoords,
                                  std::vector<std::array<float, 3>>& normals,
                                  std::vector<unsigned>& indices);

    private:
        sf::Image major_; // TODO_IMPLEMENT: provide a proper level of abstraction between Cucca and external libraries
    };


    //  Initialization info
    CUCCA_RESOURCE_INIT_INFO(HeightMap) {
    };

}; // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_HPP
