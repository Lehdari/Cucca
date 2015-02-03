/**
    Cucca Game Engine - Graphics - Material.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-03-02
**/


#ifndef CUCCA_GRAPHICS_MATERIAL_HPP
#define CUCCA_GRAPHICS_MATERIAL_HPP


#include "../../include/Core/Resource.hpp"
#include "../../include/Core/LinearAlgebra.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <vector>
#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Material) {
    public:
        //  Resource init and destroy template member functions
        CUCCA_RESOURCE_INIT_DESTROY

        Material(void);

        void useMaterial(const Matrix4Glf& mvp);

        GLuint getShaderId(void);

    private:
        ResourcePointer<ShaderProgram, ResourceId> shader_;
        std::vector<ResourcePointer<Texture, ResourceId>> textures_;

        GLuint uniformPosition_MVP_;
    };

};


#endif // CUCCA_GRAPHICS_MATERIAL_HPP
