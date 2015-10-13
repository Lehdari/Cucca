/**
    Cucca Game Engine - Graphics - MeshComponent.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
**/


#ifndef CUCCA_GRAPHICS_MESHCOMPONENT_HPP
#define CUCCA_GRAPHICS_MESHCOMPONENT_HPP


#include <Cucca/Core/Component.hpp>
#include <Cucca/Graphics/Mesh.hpp>


namespace Cucca {

    class MeshComponent : public Component {
    public:
        friend class Camera;

        MeshComponent(ResourcePointer<Mesh, ResourceId>& mesh);

        ResourcePointer<Mesh, ResourceId> getMesh(void);

    private:
        ResourcePointer<Mesh, ResourceId> mesh_;
    };

} // namespace Cucca


#endif // CUCCA_GRAPHICS_MESHCOMPONENT_HPP

