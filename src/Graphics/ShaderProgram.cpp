/**
    Cucca Game Engine - Graphics - ShaderObject.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-08
**/


#include "../../include/Graphics/ShaderProgram.hpp"
#include "../../include/Graphics/ShaderObject.hpp"
#include "../../include/Core/ResourceManager.hpp"


using namespace Cucca;


ShaderProgram::ShaderProgram(void) :
    objectId_(0)
{}

void ShaderProgram::init(const ResourceInitInfo<ShaderProgram>& initInfo,
                         const std::vector<ResourceId>& initResources,
                         const std::vector<ResourceId>& depResources,
                         ResourceManager<ResourceId>* resourceManager) {
    if (initResources.size() == 0)
        return;

    objectId_ = glCreateProgram();

    for (auto& initResourceId : initResources)
        glAttachShader(objectId_, resourceManager->getResource<ShaderObject>(initResourceId)->getId());

    glLinkProgram(objectId_);

    GLint linkStatus, infoLogLength;
    glGetProgramiv(objectId_, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        glGetShaderiv(objectId_, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = new char[infoLogLength];
        glGetProgramInfoLog(objectId_, infoLogLength, NULL, &infoLog[0]);
        fprintf(stderr, "%s", infoLog);
        throw infoLog; // TODO_EXCEPTION: throw a proper exception
    }
}

void ShaderProgram::destroy(void) {
    if (objectId_ != 0)
        glDeleteProgram(objectId_);
}

GLuint ShaderProgram::getId(void) const {
    return objectId_;
}
