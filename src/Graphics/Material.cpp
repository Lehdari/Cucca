/**
    Cucca Game Engine - Graphics - Material.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-29
**/


#include "../../include/Graphics/Material.hpp"


using namespace Cucca;


Material::Material(void) :
    uniformPosition_MVP_(0)
{}

void Material::useMaterial(const Matrix4Glf& mvp) {
    glUseProgram(shader_->getId());

    //  TODO_IMPLEMENT: we're using just one texture here. fix this.
    glActiveTexture(GL_TEXTURE0);
    textures_[0]->bind(GL_TEXTURE_2D);

    glUniformMatrix4fv(uniformPosition_MVP_, 1, GL_FALSE, mvp.data());
}

GLuint Material::getShaderId(void) {
    return shader_->getId();
}
