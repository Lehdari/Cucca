/**
    Cucca Game Engine - Graphics - Material.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-12
**/


#include "../../include/Graphics/Material.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Graphics/Texture.hpp"


using namespace Cucca;


void Material::init(const ResourceInitInfo<Material>& initInfo,
                const std::vector<ResourceId>& initResources,
                const std::vector<ResourceId>& depResources,
                ResourceManager<ResourceId>* resourceManager) {
    if (depResources.size() < 1)
        return;

    shader_ = resourceManager->getResource<ShaderProgram>(depResources[0]);

    for (auto i=1u; i<depResources.size(); ++i)
        textures_.push_back(resourceManager->getResource<Texture>(depResources[1]));

    printf("material ready, shader %s id: %u\n", depResources[0].c_str(), shader_->getId());
}

GLuint Material::getShaderId(void) {
    return shader_->getId();
}
