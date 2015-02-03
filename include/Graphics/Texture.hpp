/**
    Cucca Game Engine - Graphics - Texture.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-03
**/


#ifndef CUCCA_GRAPHICS_TEXTURE_HPP
#define CUCCA_GRAPHICS_TEXTURE_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Texture) {
    public:
        //  Resource init and destroy template member functions
        CUCCA_RESOURCE_INIT_DESTROY

        Texture(void);

    private:
        GLuint textureId_;
    };

};


#endif // CUCCA_GRAPHICS_TEXTURE_HPP

