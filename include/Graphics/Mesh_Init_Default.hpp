/**
    Cucca Game Engine - Graphics - Mesh_Init_Default.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies MeshInitInfo_Default struct and Mesh init and destroy
    member function template specializations for initializing Mesh
    resources.

    Initialization resources:
        0: VertexData
    Dependency resources:
        0: Material


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-22
**/


#ifndef CUCCA_GRAPHICS_MESH_INIT_DEFAULT_HPP
#define CUCCA_GRAPHICS_MESH_INIT_DEFAULT_HPP


#include "../Core/ResourceManager.hpp"
#include "Mesh.hpp"
#include "VertexData.hpp"


namespace Cucca {

    /// Initialization info struct
    struct MeshInitInfo_Default : public ResourceInitInfoBase { };

    /// Resource init and destroy template member function specializations
    template<>
    void Mesh::init<MeshInitInfo_Default>(const MeshInitInfo_Default& initInfo,
                                          const std::vector<ResourceId>& initResources,
                                          const std::vector<ResourceId>& depResources,
                                          ResourceManager<ResourceId>* resourceManager);

    template<>
    void Mesh::destroy<MeshInitInfo_Default>(void);

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESH_INIT_DEFAULT_HPP
