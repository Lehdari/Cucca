/**
    Cucca Game Engine - Graphics - Mesh.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#include <Cucca/Graphics/Mesh.hpp>


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
    elementBufferId_(0),
    tessellated_(false)
{}

void Mesh::draw(const Matrix4Glf& mvp) const {
    if (!tessellated_) {
        material_->useMaterial(mvp);
        glBindVertexArray(vertexArrayObjectId_);

        // TODO_IMPLEMENT: draw arrays if not using indexing
        glDrawElements(GL_TRIANGLES, nIndices_, GL_UNSIGNED_INT, (GLvoid*)0);

        glBindVertexArray(0);
    }
}

void Mesh::draw(const Matrix4Glf& model, const Matrix4Glf& camera) const {
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // TEMP

    material_->useMaterial(model, camera);
    glBindVertexArray(vertexArrayObjectId_);

    if (tessellated_) {
        glPatchParameteri(GL_PATCH_VERTICES, 4);
        glDrawElements(GL_PATCHES, nIndices_, GL_UNSIGNED_INT, (GLvoid*)0);
    }
    else
        glDrawElements(GL_TRIANGLES, nIndices_, GL_UNSIGNED_INT, (GLvoid*)0); // TODO_IMPLEMENT: draw arrays if not using indexing

    glBindVertexArray(0);
}

void Mesh::setTessellation(bool tessellated) {
    tessellated_ = tessellated;
}

bool Mesh::isTessellated(void) const {
    return tessellated_;
}

ResourcePointer<Material, ResourceId> Mesh::getMaterial(void) const {
    return material_;
}
