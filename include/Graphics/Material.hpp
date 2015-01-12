/**
    Cucca Game Engine - Graphics - Material.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-12
**/


#ifndef CUCCA_GRAPHICS_MATERIAL_HPP
#define CUCCA_GRAPHICS_MATERIAL_HPP


#include "../../include/Core/Resource.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <vector>
#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Material) {
    public:
        //  Resource init and destroy member functions
        /*
            Initialization resources:
            Dependency resources:
                0: ShaderProgram
                1-n: Texture
        */
        void init(const ResourceInitInfo<Material>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void) {}

        GLuint getShaderId(void);

    private:
        ResourcePointer<ShaderProgram, ResourceId> shader_;

        std::vector<ResourcePointer<Texture, ResourceId>> textures_;
    };

    CUCCA_RESOURCE_INIT_INFO(Material) { };
};


#endif // CUCCA_GRAPHICS_MATERIAL_HPP
