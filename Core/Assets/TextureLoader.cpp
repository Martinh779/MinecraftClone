/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include <iostream>
#include "TextureLoader.h"

#include "TexturePaths.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Libraries/stb_image/stb_image.h"
#include "../Utils/Logger.h"

namespace Resources {

    TextureLoader* TextureLoader::m_instance = nullptr;

    TextureLoader *TextureLoader::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new TextureLoader();
        }
        return m_instance;
    }


    GLuint TextureLoader::getTextureArrayId() {
        if (m_textureArrayId == 0) {
            //m_textureArrayId = loadDebugTexture(TEXTURE_PATHS);
            m_textureArrayId = loadTexture(TEXTURE_PATHS);
        }
        return m_textureArrayId;
    }


    BlockTextureLayer TextureLoader::getTextureForBlock(BlockType blockType) {
        if (blockType == BlockType::Air) {
            return {};
        }
        if (BlockTextureLayers.contains(blockType) == 0) {
            //LOG("BlockType not found: %d", LOG_ERROR, blockType);
            return {};
        }

        return BlockTextureLayers.at(blockType);
    }


    GLuint TextureLoader::loadTexture(const std::vector<std::string>& texturePaths) {
        // Load texture
        GLuint textureArrayID;
        glGenTextures(1, &textureArrayID);
        glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Calculate the size of the textures
        //stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        stbi_load(texturePaths[0].c_str(), &width, &height, &nrChannels, 0);

        CHECK_IF_GL_ERROR("Error loading texture");
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, width, height, texturePaths.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        // Load the textures and add them to the texture array
        for (int i = 0; i < texturePaths.size() - 1; i++) {
            if (unsigned char* data = stbi_load(texturePaths[i].c_str(), &width, &height, &nrChannels, 0)) {
                if (nrChannels == 3) {
                    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
                } else if (nrChannels == 4) {
                    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
                }
                stbi_image_free(data);
                CHECK_IF_GL_ERROR("Error loading texture");
            }
        }

        // Last one ist the grass block top texture so we color it green --- TODO: Remove this
        if (unsigned char* data = stbi_load(texturePaths[texturePaths.size() - 1].c_str(), &width, &height, &nrChannels, 0)) {
            colorGrassBlock(data, width, height, nrChannels);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, texturePaths.size() - 1, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            CHECK_IF_GL_ERROR("Error loading texture");
        }

        return textureArrayID;
    }

    void TextureLoader::colorGrassBlock(unsigned char* data, int width, int height, int nrChannels) {
        unsigned char grassColor[3] = {71,205,51};

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * nrChannels;

                data[index + 0] = (data[index + 0] * grassColor[0]) / 255;
                data[index + 1] = (data[index + 1] * grassColor[1]) / 255;
                data[index + 2] = (data[index + 2] * grassColor[2]) / 255;
            }
        }
    }
} // Resources