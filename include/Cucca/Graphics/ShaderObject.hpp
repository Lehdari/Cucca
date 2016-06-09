/**
    Cucca Game Engine - Graphics - ShaderObject.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-03-02
**/


#ifndef CUCCA_GRAPHICS_SHADEROBJECT_HPP
#define CUCCA_GRAPHICS_SHADEROBJECT_HPP


#include <Cucca/Core/Resource.hpp>

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(ShaderObject) {
    public:
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        ShaderObject(void);

        GLuint getId(void) const;

    private:
        GLuint objectId_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_SHADEROBJECT_HPP
