/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_TEXTURELOADER_H
#define MINECRAFTCLONE_TEXTURELOADER_H

#include <unordered_map>
#include <string>
#include <vector>
#include "glad/glad.h"
#include "glm/vec2.hpp"

namespace Resources {

    enum BlockType : std::uint8_t {
        Air,
        Dirt,
        Grass,
        Cobblestone,
        Stone,
        Sand,

        OakPlanks,
        OakLogs,
        OakLeaves,

        Poppy,
        Cactus,
    };

    struct BlockTextureLayer {
        float top;
        float side;
        float bottom;
    };

    static std::unordered_map<BlockType, BlockTextureLayer> BlockTextureLayers {
            {BlockType::Air, {}},
            {BlockType::Dirt, {0, 0, 0}},
            {BlockType::Grass, {3, 2, 0}},
            {BlockType::Stone, {1, 1, 1}},
    };

    class TextureLoader {
    public:
        static TextureLoader* getInstance();

        GLuint getTextureArrayId();

        BlockTextureLayer getTextureForBlock(BlockType blockType);

    private:
        static TextureLoader* m_instance;
        GLuint m_textureArrayId = 0;

        GLuint loadTexture(const std::vector<std::string>& texturePaths);

        void colorGrassBlock(unsigned char* data, int width, int height, int nrChannels);
    };

} // Resources

#endif //MINECRAFTCLONE_TEXTURELOADER_H
