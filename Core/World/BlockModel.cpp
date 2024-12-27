//
// Created by Martin Hertel on 10.02.2024.
//

#include <iostream>
#include "BlockModel.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "../Utils/Logger.h"


namespace Minecraft {
    BlockModel::BlockModel() : m_blockType(Resources::BlockType::Air), m_position(0, 0, 0) {
        //
    }

    BlockModel::~BlockModel() = default;


    void BlockModel::setBlockType(Resources::BlockType blockType) {
        m_blockType = blockType;
    }


    void BlockModel::setPosition(glm::vec3 position) {
        m_position = position;
    }


    void BlockModel::addToMesh(std::vector<float> &vertices, std::vector<unsigned int> &indices, GLuint &indexOffset) {
        auto blockTextureLayer = Resources::TextureLoader::getInstance()->getTextureForBlock(m_blockType);

        float x = m_position.x;
        float y = m_position.y;
        float z = m_position.z;

        // --- Bottom Face ---
        {
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
        } {
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
        } {
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
        } {
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
        } {
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
        } {
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
