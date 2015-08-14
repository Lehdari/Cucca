/**
    Cucca Game Engine - Graphics - Mesh_Init_Default.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-22
**/


#include "../../include/Debug/Debug.hpp"
#include "../../include/Graphics/Mesh_Init_Default.hpp"


using namespace Cucca;


template<>
void Cucca::Mesh::init<MeshInitInfo_Default>(const MeshInitInfo_Default& initInfo,
                                             const std::vector<ResourceId>& initResources,
                                             const std::vector<ResourceId>& depResources,
                                             ResourceManager<ResourceId>* resourceManager) {
    if (initResources.size() < 1 || depResources.size() < 1)
        return;

    auto vertexData = resourceManager->getResource<VertexData>(initResources[0]);
    material_ = resourceManager->getResource<Material>(depResources[0]);

    usingTexCoords_ = vertexData->usesTextureCoordinates();
    usingNormals_ = vertexData->usesNormals();
    usingIndexing_ = vertexData->usesIndexing();

    auto positions = vertexData->getPositions();
    auto texCoords = vertexData->getTextureCoordinates();
    auto normals = vertexData->getNormals();
    auto indices = vertexData->getIndices();

    //  create and bind the VAO
    glGenVertexArrays(1, &vertexArrayObjectId_);
    glBindVertexArray(vertexArrayObjectId_);

    //  upload the vertex data to GPU and set up the vertex attribute arrays
    glGenBuffers(1, &positionBufferId_);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferId_);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(std::array<float, 4>), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    if (usingTexCoords_) {
        glGenBuffers(1, &texCoordBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId_);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(std::array<float, 3>), &texCoords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    if (usingNormals_) {
        glGenBuffers(1, &normalBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId_);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::array<float, 3>), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    if (usingIndexing_) {
        nIndices_ = indices.size();
        glGenBuffers(1, &elementBufferId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices_ * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
    }

    //  unbind the VAO so it won't be changed outside this function
    glBindVertexArray(0);
}

template<>
void Cucca::Mesh::destroy<MeshInitInfo_Default>(void) {
    if (vertexArrayObjectId_ != 0)
        glDeleteVertexArrays(1, &vertexArrayObjectId_);

    glDeleteBuffers(1, &positionBufferId_);
    if (usingTexCoords_)
        glDeleteBuffers(1, &texCoordBufferId_);
    if (usingNormals_)
        glDeleteBuffers(1, &normalBufferId_);
    if (usingIndexing_)
        glDeleteBuffers(1, &elementBufferId_);
}
