/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "BlockModel.h"
#include "glm/glm.hpp"
#include "../Utils/Logger.h"

#define STB_IMAGE_IMPLEMENTATION


namespace Minecraft {
    /**
     * Set the block type
     * @param blockType The block type
     */
    void BlockModel::setBlockType(Resources::BlockType blockType) {
        m_blockType = blockType;
    }


    /**
     * Add the block to the mesh
     * @param position The position of the block
     * @param neighbors The neighbors of the block
     * @param vertices The vertices of the block
     * @param indices The indices of the block
     * @param indexOffset The index offset
     */
    void BlockModel::addToMesh(glm::vec3 position, std::array<bool, 6> neighbors, std::vector<float> &vertices,
                               std::vector<unsigned int> &indices, GLuint &indexOffset) {
        auto blockTextureLayer = Resources::TextureLoader::getInstance()->getTextureForBlock(m_blockType);

        float x = position.x;
        float y = position.y;
        float z = position.z;

        // --- Bottom Face ---
        if (!neighbors[0]) {
            // --- Bottom Face ---
            std::vector<GLfloat> bottomFace = {
                x, y, z, 0.0f, 1.0f, blockTextureLayer.bottom, // Bottom-left
                x + 1, y, z, 1.0f, 1.0f, blockTextureLayer.bottom, // Bottom-right
                x, y, z + 1, 0.0f, 0.0f, blockTextureLayer.bottom, // Top-left
                x + 1, y, z + 1, 1.0f, 0.0f, blockTextureLayer.bottom // Top-right
            };
            vertices.insert(vertices.end(), bottomFace.begin(), bottomFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 1, indexOffset + 2,
                               indexOffset + 1, indexOffset + 3, indexOffset + 2
                           });
            indexOffset += 4;
        }
        if (!neighbors[1]) {
            // --- Top Face ---
            std::vector<GLfloat> topFace = {
                x, y + 1, z, 0.0f, 0.0f, blockTextureLayer.top, // Bottom-left
                x + 1, y + 1, z, 1.0f, 0.0f, blockTextureLayer.top, // Bottom-right
                x, y + 1, z + 1, 0.0f, 1.0f, blockTextureLayer.top, // Top-left
                x + 1, y + 1, z + 1, 1.0f, 1.0f, blockTextureLayer.top // Top-right
            };
            vertices.insert(vertices.end(), topFace.begin(), topFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 2, indexOffset + 1,
                               indexOffset + 1, indexOffset + 2, indexOffset + 3
                           });
            indexOffset += 4;
        }
        if (!neighbors[2]) {
            // --- Left Face ---
            std::vector<GLfloat> leftFace = {
                x, y, z, 0.0f, 1.0f, blockTextureLayer.side, // Bottom-left
                x, y, z + 1, 1.0f, 1.0f, blockTextureLayer.side, // Bottom-right
                x, y + 1, z, 0.0f, 0.0f, blockTextureLayer.side, // Top-left
                x, y + 1, z + 1, 1.0f, 0.0f, blockTextureLayer.side // Top-right
            };
            vertices.insert(vertices.end(), leftFace.begin(), leftFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 1, indexOffset + 2,
                               indexOffset + 1, indexOffset + 3, indexOffset + 2
                           });
            indexOffset += 4;
        }
        if (!neighbors[3]) {
            // --- Right Face ---
            std::vector<GLfloat> rightFace = {
                x + 1, y, z, 1.0f, 1.0f, blockTextureLayer.side, // Bottom-left
                x + 1, y, z + 1, 0.0f, 1.0f, blockTextureLayer.side, // Bottom-right
                x + 1, y + 1, z, 1.0f, 0.0f, blockTextureLayer.side, // Top-left
                x + 1, y + 1, z + 1, 0.0f, 0.0f, blockTextureLayer.side // Top-right
            };
            vertices.insert(vertices.end(), rightFace.begin(), rightFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 2, indexOffset + 1,
                               indexOffset + 1, indexOffset + 2, indexOffset + 3
                           });
            indexOffset += 4;
        }
        if (!neighbors[4]) {
            // --- Back Face ---
            std::vector<GLfloat> backFace = {
                x, y, z, 1.0f, 1.0f, blockTextureLayer.side, // Bottom-left
                x + 1, y, z, 0.0f, 1.0f, blockTextureLayer.side, // Bottom-right
                x, y + 1, z, 1.0f, 0.0f, blockTextureLayer.side, // Top-left
                x + 1, y + 1, z, 0.0f, 0.0f, blockTextureLayer.side // Top-right
            };
            vertices.insert(vertices.end(), backFace.begin(), backFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 2, indexOffset + 1,
                               indexOffset + 1, indexOffset + 2, indexOffset + 3
                           });
            indexOffset += 4;
        }
        if (!neighbors[5]) {
            // --- Front Face ---
            std::vector<GLfloat> frontFace = {
                x, y, z + 1, 0.0f, 1.0f, blockTextureLayer.side, // Bottom-left
                x + 1, y, z + 1, 1.0f, 1.0f, blockTextureLayer.side, // Bottom-right
                x, y + 1, z + 1, 0.0f, 0.0f, blockTextureLayer.side, // Top-left
                x + 1, y + 1, z + 1, 1.0f, 0.0f, blockTextureLayer.side // Top-right
            };
            vertices.insert(vertices.end(), frontFace.begin(), frontFace.end());

            indices.insert(indices.end(), {
                               indexOffset + 0, indexOffset + 1, indexOffset + 2,
                               indexOffset + 1, indexOffset + 3, indexOffset + 2
                           });
            indexOffset += 4;
        }
    }

} // Minecraft
