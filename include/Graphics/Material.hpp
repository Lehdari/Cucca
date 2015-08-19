/**
    Cucca Game Engine - Graphics - Material.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
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
        //  Resource init and destroy template member function declarations
        CUCCA_RESOURCE_INIT_DESTROY_DECL

        Material(void);

        void useMaterial(const Matrix4Glf& mvp) const;
        //  note ordering in initialization info (model matrix name first)
        //  also known as world and VP matrices
        void useMaterial(const Matrix4Glf& model, const Matrix4Glf& camera) const;

        GLuint getShaderId(void) const;

    private:
        ResourcePointer<ShaderProgram, ResourceId> shader_;
        std::vector<ResourcePointer<Texture, ResourceId>> textures_;

        std::vector<GLint> uniformLocations_Sampler2D_;
        std::vector<GLint> uniformLocations_Mat4_;

        void bindTextures(void) const;
    };

};


#endif // CUCCA_GRAPHICS_MATERIAL_HPP
