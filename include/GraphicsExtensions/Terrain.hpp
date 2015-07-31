/**
    Cucca Game Engine - GraphicsExtensions - Terrain.hpp

    Terrain class implements a dynamically loaded terrain demonstrating
    Cucca Game Engine's asynchronous resource loading capabilities.

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-21
**/


#ifndef CUCCA_GRAPHICSEXTENSIONS_TERRAIN_HPP
#define CUCCA_GRAPHICSEXTENSIONS_TERRAIN_HPP


#include "../Core/ResourceId.hpp"
#include "../Core/ResourcePointer.hpp"
#include "../Core/LinearAlgebra.hpp"
#include "HeightMap.hpp"
#include "../Graphics/Material.hpp"


namespace Cucca {

    //  Forward declarations
    class Node;

    //  Structs/classes
    class Terrain {
    public:
        Terrain(ResourceManager<ResourceId>& resourceManager,
                Node* node,
                const ResourceId& heightMapId,
                const ResourceId& materialId,
                const std::string& segmentName);

        /*  update the terrain
            loadingRadius: radius inside which new segments will be initialized
                           (measured from position to segments' middle point)
            activationRadius: radius inside which segments will be created and added
                              to terrains root node   */
        void update(const Vector3Glf& position,
                    float loadingRadius,
                    float activationRadius);

    private:
        enum SegmentStatus {
            SEGMENTSTATUS_UNLOADED,
            SEGMENTSTATUS_LOADED,
            SEGMENTSTATUS_ACTIVE
        };

        struct SegmentData {
            SegmentStatus status;
            Node* node;
            ResourceId vertexDataResourceId;
            ResourceId meshResourceId;
        };

        ResourceManager<ResourceId>& resourceManager_;
        Node* node_;
        ResourcePointer<HeightMap> heightMap_;
        ResourcePointer<Material> material_;
        std::string segmentName_;

        std::vector<std::vector<SegmentData>> segmentData_;
    };

}; // namespace Cucca


#endif // CUCCA_GRAPHICSEXTENSIONS_TERRAIN_HPP

