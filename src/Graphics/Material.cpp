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


Material::Material(void) :
    uniformPosition_MVP_(0)
{}

void Material::init(const ResourceInitInfo<Material>& initInfo,
                const std::vector<ResourceId>& initResources,
                const std::vector<ResourceId>& depResources,
                ResourceManager<ResourceId>* resourceManager) {
    if (depResources.size() < 1)
        return;

    shader_ = resourceManager->getResource<ShaderProgram>(depResources[0]);

    for (auto i=1u; i<depResources.size(); ++i)
        textures_.push_back(resourceManager->getResource<Texture>(depResources[1]));

    uniformPosition_MVP_ = glGetUniformLocation(shader_->getId(), "MVP");
}

void Material::useMaterial(const Matrix4Glf& mvp) {
    glUseProgram(shader_->getId());
    glUniformMatrix4fv(uniformPosition_MVP_, 1, GL_FALSE, mvp.data());
}

GLuint Material::getShaderId(void) {
    return shader_->getId();
}
