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
    @date       2015-08-19
**/


#ifndef CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
#define CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP


#include <Cucca/Debug/Debug.hpp>
#include <Cucca/Core/ResourceManager.hpp>
#include <Cucca/Graphics/Material.hpp>

#include <vector>
#include <string>


namespace Cucca {

    /// Initialization info struct
    struct MaterialInitInfo_Default : public ResourceInitInfoBase {
        /*  1st sampler2D: diffuse  */
        std::vector<std::string> uniformSampler2DNames;

        /*  1st mat4: mvp / model matrix
            2nd mat4: camera matrix         */
        std::vector<std::string> uniformMat4Names;
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(Material, MaterialInitInfo_Default) {
        if (depResources.size() < 1)
            return;

        shader_ = resourceManager->getResource<ShaderProgram>(depResources[0]);

        for (auto i=1u; i<depResources.size(); ++i)
            textures_.push_back(resourceManager->getResource<Texture>(depResources[i]));

        //  fetch uniform locations
        for (auto& name : initInfo.uniformSampler2DNames)
            uniformLocations_Sampler2D_.emplace_back(glGetUniformLocation(shader_->getId(), name.c_str()));
        for (auto& name : initInfo.uniformMat4Names)
            uniformLocations_Mat4_.emplace_back(glGetUniformLocation(shader_->getId(), name.c_str()));
    }

    CUCCA_RESOURCE_DESTROY(Material, MaterialInitInfo_Default) {}

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MATERIAL_INIT_DEFAULT_HPP
