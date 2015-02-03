/**
    Cucca Game Engine - GraphicsExtensions - HeightMap_Default.hpp

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
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_DEFAULT_HPP
#define CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_DEFAULT_HPP


#include "../Core/ResourceManager.hpp"
#include "HeightMap.hpp"


namespace Cucca {

    /// Initialization info struct
    struct HeightMapInitInfo_Default : public ResourceInitInfoBase { };


    /// Resource init and destroy template member function specializations
    template<>
    void HeightMap::init<HeightMapInitInfo_Default>(const HeightMapInitInfo_Default& initInfo,
                                                    const std::vector<ResourceId>& initResources,
                                                    const std::vector<ResourceId>& depResources,
                                                    ResourceManager<ResourceId>* resourceManager) {
        if (initResources.size() < 1)
            return; // TODO_EXCEPTION: maybe throw a proper exception instead?

        auto majorBinary = resourceManager->getResource<Binary>(initResources[0]);

        major_.loadFromMemory(majorBinary->getBufferPtr(), majorBinary->getBufferSize());
    }

    template<>
    void HeightMap::destroy<HeightMapInitInfo_Default>(void) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_HEIGHTMAP_DEFAULT_HPP
