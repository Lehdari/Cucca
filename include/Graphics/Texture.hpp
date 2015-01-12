/**
    Cucca Game Engine - Graphics - Texture.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-12
**/


#ifndef CUCCA_GRAPHICS_TEXTURE_HPP
#define CUCCA_GRAPHICS_TEXTURE_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Texture) {
    public:
        Texture(void);

        //  Resource init and destroy member functions
        /*
            Initialization resources:
                0: Binary (image file)
            Dependency resources:
        */
        void init(const ResourceInitInfo<Texture>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

    private:
        GLuint textureId_;
    };

    CUCCA_RESOURCE_INIT_INFO(Texture) {
        enum Source {
            SOURCE_BINARY_PNG      //  Loaded from .png file
        } source;

        GLint wrapS;
        GLint wrapT;
        GLint minFiltering;
        GLint magFiltering;
    };
};


#endif // CUCCA_GRAPHICS_TEXTURE_HPP

