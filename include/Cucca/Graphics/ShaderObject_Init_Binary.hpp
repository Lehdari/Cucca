/**
    Cucca Game Engine - Graphics - ShaderObject_Init_Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies ShaderObjectInitInfo_Binary struct and ShaderObject
    init and destroy member function template specializations for
    initializing ShaderObject resources from Binary resources.

    Initialization resources:
        0: Binary
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICS_SHADEROBJECT_INIT_BINARY_HPP
#define CUCCA_GRAPHICS_SHADEROBJECT_INIT_BINARY_HPP



#include <Cucca/Core/ResourceManager.hpp>
#include <Cucca/Graphics/ShaderObject.hpp>

#include <Cucca/Core/Binary.hpp>


namespace Cucca {

    /// Initialization info struct
    struct ShaderObjectInitInfo_Binary : public ResourceInitInfoBase {
        enum Source {
            SOURCE_GLSL,       //  Loaded from plain GLSL code
            SOURCE_BINARY      //  Loaded from precompiled binary
        } source;

        GLenum type; //  Shader type
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(ShaderObject, ShaderObjectInitInfo_Binary) {
        switch (initInfo.source) {
        case ShaderObjectInitInfo_Binary::SOURCE_GLSL:
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
                    fprintf(stderr, "%s", infoLog);
                    throw infoLog; // TODO_EXCEPTION: throw a proper exception
                }
            }
        break;

        case ShaderObjectInitInfo_Binary::SOURCE_BINARY:
            throw "ShaderObject: binary loading not implemented"; // TODO_IMPLEMENT, TODO_EXCEPTION: throw a proper exception
        break;
        }
    }

    CUCCA_RESOURCE_DESTROY(ShaderObject, ShaderObjectInitInfo_Binary) {
        if (objectId_ != 0)
            glDeleteShader(objectId_);
    }

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADEROBJECT_INIT_BINARY_HPP

