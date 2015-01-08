/**
    Cucca Game Engine - Graphics - ShaderObject.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-08
**/


#ifndef CUCCA_GRAPHICS_SHADEROBJECT_HPP
#define CUCCA_GRAPHICS_SHADEROBJECT_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(ShaderObject) {
    public:
        ShaderObject(void);

        //  Resource init and destroy member functions
        void init(const ResourceInitInfo<ShaderObject>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        GLuint getId(void) const;

    private:
        GLuint objectId_;
    };

    CUCCA_RESOURCE_INIT_INFO(ShaderObject) {
        enum Source {
            SOURCE_CODE,       //  Loaded from plain GLSL code
            SOURCE_BINARY      //  Loaded from precompiled binary
        } source;

        GLenum type; //  Shader type
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADEROBJECT_HPP
