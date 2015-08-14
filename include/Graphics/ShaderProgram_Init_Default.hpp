/**
    Cucca Game Engine - Graphics - ShaderProgram_Init_Default.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies ShaderProgramInitInfo_Default struct and
    ShaderProgram init and destroy member function template
    specializations for initializing ShaderProgram resources from
    ShaderObjects.

    Initialization resources:
        0-n: ShaderObject
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICS_SHADERPROGRAM_INIT_DEFAULT_HPP
#define CUCCA_GRAPHICS_SHADERPROGRAM_INIT_DEFAULT_HPP


#include "../Core/ResourceManager.hpp"
#include "ShaderProgram.hpp"
#include "ShaderObject.hpp"


namespace Cucca {

    /// Initialization info struct
    struct ShaderProgramInitInfo_Default : public ResourceInitInfoBase { };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(ShaderProgram, ShaderProgramInitInfo_Default) {
        if (initResources.size() == 0)
            return;

        programId_ = glCreateProgram();

        for (auto& initResourceId : initResources)
            glAttachShader(programId_, resourceManager->getResource<ShaderObject>(initResourceId)->getId());

        glLinkProgram(programId_);

        GLint linkStatus, infoLogLength;
        glGetProgramiv(programId_, GL_LINK_STATUS, &linkStatus);

        if (linkStatus == GL_FALSE) {
            glGetShaderiv(programId_, GL_INFO_LOG_LENGTH, &infoLogLength);

            char* infoLog = new char[infoLogLength];
            glGetProgramInfoLog(programId_, infoLogLength, NULL, &infoLog[0]);
            fprintf(stderr, "%s", infoLog);
            throw infoLog; // TODO_EXCEPTION: throw a proper exception
        }
    }

    CUCCA_RESOURCE_DESTROY(ShaderProgram, ShaderProgramInitInfo_Default) {
        if (programId_ != 0)
            glDeleteProgram(programId_);
    }

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADERPROGRAM_INIT_DEFAULT_HPP
