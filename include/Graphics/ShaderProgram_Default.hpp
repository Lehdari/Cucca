/**
    Cucca Game Engine - Graphics - ShaderProgram_Default.hpp

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


#ifndef CUCCA_GRAPHICS_SHADERPROGRAM_DEFAULT_HPP
#define CUCCA_GRAPHICS_SHADERPROGRAM_DEFAULT_HPP


#include "../Core/ResourceManager.hpp"
#include "ShaderProgram.hpp"
#include "ShaderObject.hpp"


namespace Cucca {

    /// Initialization info struct
    struct ShaderProgramInitInfo_Default : public ResourceInitInfoBase { };


    /// Resource init and destroy template member function specializations
    template<>
    void ShaderProgram::init<ShaderProgramInitInfo_Default>(const ShaderProgramInitInfo_Default& initInfo,
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

    template<>
    void ShaderProgram::destroy<ShaderProgramInitInfo_Default>(void) {
        if (objectId_ != 0)
            glDeleteProgram(objectId_);
    }

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADERPROGRAM_DEFAULT_HPP
