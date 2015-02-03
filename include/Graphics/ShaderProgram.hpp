/**
    Cucca Game Engine - Graphics - ShaderProgram.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-03
**/


#ifndef CUCCA_GRAPHICS_SHADERPROGRAM_HPP
#define CUCCA_GRAPHICS_SHADERPROGRAM_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(ShaderProgram) {
    public:
        ShaderProgram(void);

        //  Resource init and destroy member functions
        template<typename ResourceInitInfoType_T>
        void init(const ResourceInitInfoType_T& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);

        template<typename ResourceInitInfoType_T>
        void destroy(void);

        GLuint getId(void) const;

    private:
        GLuint objectId_;
    };

    CUCCA_RESOURCE_INIT_INFO(ShaderProgram) { };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADERPROGRAM_HPP

