/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_BLOCKMODEL_H
#define MINECRAFTCLONE_BLOCKMODEL_H

#include <vector>
#include "../Assets/TextureLoader.h"
#include "../Physics/Collision.h"
#include "../Physics/BoundingBox.h"


namespace Minecraft {
    class BlockModel {
    public:
        BlockModel() = default;

        ~BlockModel() = default;

        [[nodiscard]] Resources::BlockType getBlockType() const { return m_blockType; }

        void setBlockType(Resources::BlockType blockType);

        void addToMesh(glm::vec3 position, std::array<bool, 6> neighbors, std::vector<float> &vertices, std::vector<unsigned int> &indices, GLuint &indexOffset);

    protected:
        Resources::BlockType m_blockType = Resources::BlockType::Air;
    };
} // Minecraft
#endif //MINECRAFTCLONE_BLOCKMODEL_H
