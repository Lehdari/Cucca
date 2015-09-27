/**
    Cucca Game Engine - Graphics - Texture.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-29
**/


#ifndef CUCCA_GRAPHICS_TEXTURE_HPP
#define CUCCA_GRAPHICS_TEXTURE_HPP


#include <Cucca/Core/Resource.hpp>

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Texture) {
    public:
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        Texture(void);

        //  Bind the texture to given OpenGL target
        void bind(GLenum target) const;

    private:
        GLuint textureId_;
    };

};


#endif // CUCCA_GRAPHICS_TEXTURE_HPP

