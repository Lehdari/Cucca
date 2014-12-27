/**
    Cucca Game Engine - Core - VertexData.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#ifndef CUCCA_GRAPHICS_VERTEXDATA_HPP
#define CUCCA_GRAPHICS_VERTEXDATA_HPP


#include "../../include/Core/Resource.hpp"

#include <GL/glew.h>


namespace Cucca {

    CUCCA_RESOURCE(VertexData) {
    public:
        //  Resource init and destroy member functions
        void init(const ResourceInitInfo<VertexData>& initInfo,
                  const std::vector<ResourceId>& initResources,
                  const std::vector<ResourceId>& depResources,
                  ResourceManager<ResourceId>* resourceManager);
        void destroy(void);

        GLuint getId(void) const;

    private:
        GLuint objectId_;
    };

    CUCCA_RESOURCE_INIT_INFO(VertexData) {
        enum Source {
            SOURCE_BINARY_OBJ      //  Loaded from precompiled binary
        } source;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_VERTEXDATA_HPP
