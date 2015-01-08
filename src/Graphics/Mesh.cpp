/**
    Cucca Game Engine - Graphics - Mesh.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-08
**/


#include "../../include/Graphics/Mesh.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Graphics/VertexData.hpp"


using namespace Cucca;


Mesh::Mesh(void) :
    usingTexCoords_(false),
    usingNormals_(false),
    usingIndexing_(false),
    positionBufferId_(0),
    texCoordBufferId_(0),
    normalBufferId_(0),
    elementBufferId_(0)
{}

void Mesh::init(const ResourceInitInfo<Mesh>& initInfo,
                const std::vector<ResourceId>& initResources,
                const std::vector<ResourceId>& depResources,
                ResourceManager<ResourceId>* resourceManager) {
    if (initResources.size() == 0)
        return;

    auto vertexData = resourceManager->getResource<VertexData>(initResources[0]);

    usingTexCoords_ = vertexData->usesTextureCoordinates();
    usingNormals_ = vertexData->usesNormals();
    usingIndexing_ = vertexData->usesIndexing();

    auto positions = vertexData->getPositions();
    auto texCoords = vertexData->getTextureCoordinates();
    auto normals = vertexData->getNormals();
    auto indices = vertexData->getIndices();

    glGenBuffers(1, &positionBufferId_);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferId_);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(std::array<float, 4>), &positions[0], GL_STATIC_DRAW);

    if (usingTexCoords_) {
        glGenBuffers(1, &texCoordBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId_);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(std::array<float, 3>), &texCoords[0], GL_STATIC_DRAW);
    }

    if (usingNormals_) {
        glGenBuffers(1, &normalBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId_);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::array<float, 3>), &normals[0], GL_STATIC_DRAW);
    }

    if (usingIndexing_) {
        glGenBuffers(1, &elementBufferId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
    }
}

void Mesh::destroy(void) {
    glDeleteBuffers(1, &positionBufferId_);
    if (usingTexCoords_)
        glGenBuffers(1, &texCoordBufferId_);
    if (usingNormals_)
        glGenBuffers(1, &normalBufferId_);
    if (usingIndexing_)
        glGenBuffers(1, &elementBufferId_);
}
