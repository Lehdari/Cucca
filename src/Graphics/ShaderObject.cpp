/**
    Cucca Game Engine - Graphics - ShaderObject.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#include "../../include/Graphics/ShaderObject.hpp"
#include "../../include/Core/Binary.hpp"
#include "../../include/Core/ResourceManager.hpp"


using namespace Cucca;


ShaderObject::ShaderObject(void) :
    objectId_(0)
{}

void ShaderObject::init(const ResourceInitInfo<ShaderObject>& initInfo,
                        const std::vector<ResourceId>& initResources,
                        const std::vector<ResourceId>& depResources,
                        ResourceManager<ResourceId>* resourceManager) {
    switch (initInfo.source) {
    case ResourceInitInfo<ShaderObject>::SOURCE_CODE:
        {
            if (initResources.size() == 0)
                objectId_ = 0;

            auto src = resourceManager->getResource<Binary>(initResources[0]);
            const char* srcPtr = src->getBufferPtr();

            objectId_ = glCreateShader(initInfo.type);

            glShaderSource(objectId_, 1, &srcPtr , NULL);
            glCompileShader(objectId_);

            GLint compileStatus, infoLogLength;
            glGetShaderiv(objectId_, GL_COMPILE_STATUS, &compileStatus);

            if (compileStatus == GL_FALSE) {
                glGetShaderiv(objectId_, GL_INFO_LOG_LENGTH, &infoLogLength);

                char* infoLog = new char[infoLogLength];
                glGetShaderInfoLog(objectId_, infoLogLength, NULL, &infoLog[0]);
                throw infoLog; // TODO_EXCEPTION: throw a proper exception
            }
        }
    break;

    case ResourceInitInfo<ShaderObject>::SOURCE_BINARY:
        throw "ShaderObject: binary loading not implemented"; // TODO_EXCEPTION: throw a proper exception
    break;
    }
}

void ShaderObject::destroy(void) {
    if (objectId_ != 0)
        glDeleteShader(objectId_);
}

GLuint ShaderObject::getId(void) const {
    return objectId_;
}
