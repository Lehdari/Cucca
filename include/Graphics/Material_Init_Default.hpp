/**
    Cucca Game Engine - Graphics - Material_Init_Default.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies MaterialInitInfo_Default struct and Material init
    and destroy member function template specializations for
    initializing Material resources.

    Initialization resources:
        none
    Dependency resources:
        0: ShaderProgram
        1-n: Texture


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
#define CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP


#include "../Core/ResourceManager.hpp"
#include "Material.hpp"


namespace Cucca {

    /// Initialization info struct
    struct MaterialInitInfo_Default : public ResourceInitInfoBase { };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(Material, MaterialInitInfo_Default) {
        if (depResources.size() < 1)
            return;

        shader_ = resourceManager->getResource<ShaderProgram>(depResources[0]);

        for (auto i=1u; i<depResources.size(); ++i)
            textures_.push_back(resourceManager->getResource<Texture>(depResources[1]));

        uniformPosition_MVP_ = glGetUniformLocation(shader_->getId(), "MVP");
    }

    CUCCA_RESOURCE_DESTROY(Material, MaterialInitInfo_Default) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
