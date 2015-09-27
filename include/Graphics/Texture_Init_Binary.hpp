/**
    Cucca Game Engine - Graphics - Texture_Binary.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file is a resource initialization file.
    It specifies TextureInitInfo_Binary struct and Texture init
    and destroy member function template specializations for
    initializing Texture resources from a Binary resource.

    Initialization resources:
        0: Binary
    Dependency resources:
        none


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-02-04
**/


#ifndef CUCCA_GRAPHICS_TEXTURE_BINARY_HPP
#define CUCCA_GRAPHICS_TEXTURE_BINARY_HPP


#include <Cucca/Core/ResourceManager.hpp>
#include <Cucca/Graphics/Texture.hpp>
#include <Cucca/Core/Binary.hpp>

// TODO_IMPLEMENT: provide a proper level of abstraction between Cucca and external libraries
#include <SFML/Graphics/Image.hpp> // TEMP


namespace Cucca {

    /// Initialization info struct
    struct TextureInitInfo_Binary : public ResourceInitInfoBase {
        enum Source {
            SOURCE_BINARY_PNG      //  Loaded from .png file
        } source;

        GLint wrapS;
        GLint wrapT;
        GLint minFiltering;
        GLint magFiltering;
    };


    /// Resource init and destroy template member function specializations
    CUCCA_RESOURCE_INIT(Texture, TextureInitInfo_Binary) {
        if (initResources.size() < 1)
            return;

        switch (initInfo.source) {
        case TextureInitInfo_Binary::SOURCE_BINARY_PNG:
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

    CUCCA_RESOURCE_DESTROY(Texture, TextureInitInfo_Binary) {
        if (textureId_ != 0)
            glDeleteTextures(1, &textureId_);
    }

} // namespace Cucca


#endif // CUCCA_GRAPHICS_TEXTURE_BINARY_HPP
