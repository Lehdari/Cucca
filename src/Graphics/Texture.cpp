/**
    Cucca Game Engine - Graphics - Texture.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-12
**/


#include "../../include/Graphics/Texture.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"

// TODO_IMPLEMENT: provide a proper level of abstraction between Cucca and external libraries
#include <SFML/Graphics/Image.hpp> // TEMP


using namespace Cucca;


Texture::Texture(void) :
    textureId_(0)
{}

void Texture::init(const ResourceInitInfo<Texture>& initInfo,
                   const std::vector<ResourceId>& initResources,
                   const std::vector<ResourceId>& depResources,
                   ResourceManager<ResourceId>* resourceManager) {
    if (initResources.size() < 1)
        return;

    switch (initInfo.source) {
    case ResourceInitInfo<Texture>::SOURCE_BINARY_PNG:
        {
            auto buffer = resourceManager->getResource<Binary>(initResources[0]);

            sf::Image img;
            img.loadFromMemory(buffer->getBufferPtr(), buffer->getBufferSize());

            glGenTextures(1, &textureId_);
            glBindTexture(GL_TEXTURE_2D, textureId_);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, initInfo.wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, initInfo.wrapT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, initInfo.minFiltering);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, initInfo.magFiltering);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    break;
    }
}

void Texture::destroy(void) {
    if (textureId_ != 0)
        glDeleteTextures(1, &textureId_);
}
