/**
    Cucca Game Engine - Graphics - Mesh.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#include "../../include/Graphics/Mesh.hpp"


using namespace Cucca;


Mesh::Mesh(void) :
    vertexArrayObjectId_(0),
    usingTexCoords_(false),
    usingNormals_(false),
    usingIndexing_(false),
    nIndices_(0),
    positionBufferId_(0),
    texCoordBufferId_(0),
    normalBufferId_(0),
    elementBufferId_(0)
{}

void Mesh::draw(const Matrix4Glf& mvp) {
    material_->useMaterial(mvp);
    glBindVertexArray(vertexArrayObjectId_);

    // TODO_IMPLEMENT: draw arrays if not using indexing
    glDrawElements(GL_TRIANGLES, nIndices_, GL_UNSIGNED_INT, (GLvoid*)0);

    glBindVertexArray(0);
}
