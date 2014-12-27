/**
    Cucca Game Engine - Graphics - Mesh.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#ifndef CUCCA_GRAPHICS_MESH_HPP
#define CUCCA_GRAPHICS_MESH_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(Mesh) {
    public:
        //  Resource init and destroy member functions
        void init(const ResourceInitInfo<Mesh>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        GLuint getId(void) const;

    private:
        GLuint objectId_;
    };

    CUCCA_RESOURCE_INIT_INFO(Mesh) { };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESH_HPP
