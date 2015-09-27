/**
    Cucca Game Engine - Graphics - Material.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#include <Cucca/Graphics/Material.hpp>


using namespace Cucca;


Material::Material(void) {}

void Material::useMaterial(const Matrix4Glf& mvp) const {
    glUseProgram(shader_->getId());
    bindTextures();
    glUniformMatrix4fv(uniformLocations_Mat4_[0], 1, GL_FALSE, mvp.data());
}

void Material::useMaterial(const Matrix4Glf& model, const Matrix4Glf& camera) const {
    glUseProgram(shader_->getId());
    bindTextures();
    glUniformMatrix4fv(uniformLocations_Mat4_[0], 1, GL_FALSE, model.data());
    glUniformMatrix4fv(uniformLocations_Mat4_[1], 1, GL_FALSE, camera.data());
}

GLuint Material::getShaderId(void) const {
    return shader_->getId();
}

void Material::bindTextures(void) const {
    auto nValidBinds = std::min(textures_.size(), uniformLocations_Sampler2D_.size());
    for (auto i=0u; i<nValidBinds; ++i) {
        glActiveTexture(GL_TEXTURE0+i);
        textures_[i]->bind(GL_TEXTURE_2D);
        glUniform1i(uniformLocations_Sampler2D_[i], i);
    }
}
