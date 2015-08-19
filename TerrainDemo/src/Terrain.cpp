/**
    Cucca Game Engine - TerrainDemo - Terrain.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-21
**/


#include "../include/Terrain.hpp"
#include "../include/VertexData_Init_HeightMap.hpp"
#include "../../include/Debug/Debug.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Node.hpp"
#include "../../include/Graphics/Mesh_Init_Default.hpp"
#include "../../include/Graphics/MeshComponent.hpp"
#include "../../include/Graphics/TransformationComponent.hpp"


using namespace Cucca;


Terrain::Terrain(ResourceManager<ResourceId>& resourceManager,
                 Node* node,
                 const ResourceId& heightMapId,
                 const ResourceId& materialId,
                 const std::string& segmentName) :
    resourceManager_(resourceManager),
    node_(node),
    heightMap_(resourceManager.getResource<HeightMap>(heightMapId)),
    material_(resourceManager.getResource<Material>(materialId)),
    segmentName_(segmentName)
{
    //  produce the VertexData initialization infos and add them to the resource manager
    //  and create initial segment status vector
    unsigned numXSegments = heightMap_->getNumXSegments();
    unsigned numYSegments = heightMap_->getNumYSegments();

    segmentData_.reserve(numXSegments);

    for (auto i=0u; i<numXSegments; ++i) {
        std::vector<SegmentData> segDataCol;

        for (auto j=0u; j<numYSegments; ++j) {
            SegmentData segData;
            segData.status = SEGMENTSTATUS_UNLOADED;
            segData.node = nullptr;
            segData.vertexDataResourceId = ResourceId(segmentName_ + "_VERTEXDATA", numXSegments*j + i);
            segData.meshResourceId = ResourceId(segmentName_ + "_MESHDATA", numXSegments*j + i);

            VertexDataInitInfo_HeightMap vertexDataInitInfo;
            vertexDataInitInfo.segmentX = i;
            vertexDataInitInfo.segmentY = j;
            resourceManager_.addResourceInfo<VertexData>(segData.vertexDataResourceId,
                                                         vertexDataInitInfo,
                                                         std::vector<ResourceId>{ heightMapId },
                                                         std::vector<ResourceId>());

            MeshInitInfo_Default meshInitInfo;
            resourceManager_.addResourceInfo<Mesh>(segData.meshResourceId,
                                                   meshInitInfo,
                                                   std::vector<ResourceId>{ segData.vertexDataResourceId },
                                                   std::vector<ResourceId>{ materialId },
                                                   true);

            segDataCol.push_back(std::move(segData));
        }

        segmentData_.push_back(std::move(segDataCol));
    }
}

void Terrain::update(const Vector3Glf& position,
                     float loadingRadius,
                     float activationRadius) {
    unsigned numXSegments = heightMap_->getNumXSegments();
    unsigned numYSegments = heightMap_->getNumYSegments();
    float segXSize = heightMap_->getSegmentXSize();
    float segYSize = heightMap_->getSegmentYSize();
    float offsetX = heightMap_->getOffsetX();
    float offsetY = heightMap_->getOffsetY();

    //  determine area to check
    int xMin = std::max(0, (int)((position(0) - offsetX - loadingRadius) / segXSize));
    int yMin = std::max(0, (int)((position(2) - offsetY - loadingRadius) / segYSize));
    int xMax = std::min((int)numXSegments, (int)(((position(0) - offsetX + loadingRadius) / segXSize) + 1));
    int yMax = std::min((int)numYSegments, (int)(((position(2) - offsetY + loadingRadius) / segYSize) + 1));

    for (auto j=yMin; j<yMax; ++j) {
        for (auto i=xMin; i<xMax; ++i) {
            float x = offsetX + (i+0.5f)*segXSize - position(0);
            float y = offsetY + (j+0.5f)*segYSize - position(2);
            float dis = sqrtf(x*x + y*y);

            if (dis < loadingRadius && dis > activationRadius) {
                if (segmentData_[i][j].status == SEGMENTSTATUS_UNLOADED) {
                    //  segment entering loading radius, preload the resource
                    CUCCA_DPRINTF("Terrain: preloading node resources (%, %)", i , j);
                    resourceManager_.loadResource(segmentData_[i][j].meshResourceId);
                }
                else if (segmentData_[i][j].status == SEGMENTSTATUS_ACTIVE) {
                    //  segment exiting activation radius, delete node
                    CUCCA_DPRINTF("Terrain: unloading node (%, %)", i , j);
                    node_->removeChild(segmentData_[i][j].node);
                }

                segmentData_[i][j].status = SEGMENTSTATUS_LOADED;
            }
            else if (dis < activationRadius && segmentData_[i][j].status != SEGMENTSTATUS_ACTIVE) {
                //  segment entering activation radius, create new node
                CUCCA_DPRINTF("Terrain: creating new node (%, %)", i , j);
                Node newNode;
                auto meshPointer = resourceManager_.getResource<Mesh>(segmentData_[i][j].meshResourceId);
                newNode.addComponent(MeshComponent(meshPointer));
                auto transformationComponent = newNode.addComponent(TransformationComponent());
                transformationComponent->translate(Vector3Glf(offsetX + i*segXSize, 0.0f, offsetY + j*segYSize));

                segmentData_[i][j].node = node_->addChild(std::move(newNode));
                segmentData_[i][j].status = SEGMENTSTATUS_ACTIVE;
            }
        }
    }
}
