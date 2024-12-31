/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "Chunk.h"

#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Math/PerlinNoise.h"
#include "../Utils/Logger.h"
#include "../Player/Camera.h"
#include "../Player/Player.h"

namespace Minecraft {
    class Camera;

    /**
     * Default constructor
     */
    Chunk::Chunk(std::pair<int, int> position) {
        m_position = position;
        fillChunk();
        addBlocksToChunkMesh();
    }


    /**
     * Destructor
     */
    Chunk::~Chunk() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }


    /**
     * Uses the perlin noise to fill the chunk with blocks / change the block types
     */
    void Chunk::fillChunk() {
        Math::PerlinNoise* perlinNoise = Math::PerlinNoise::getInstance();
        for (int x = 0; x < m_blocks.getX(); x++) {
            for (int z = 0; z < m_blocks.getZ(); z++) {  // z-axis corresponds to height
                // Calculate the height of the terrain at this point
                int height = perlinNoise->calculatePerlin(m_position.first + x, m_position.second + z);

                // Iterate through the height of the terrain
                for (int y = m_blocks.getY() - 1; y >= 0; y--) {
                    BlockModel& block = m_blocks(x, y, z);
                    if (y < height - 10) {
                        block.setBlockType(Resources::BlockType::Stone);
                    } else if (y < height - 5) {
                        block.setBlockType(Resources::BlockType::Dirt);
                    } else if (y < height) {
                        block.setBlockType(Resources::BlockType::Grass);
                    } else {
                        block.setBlockType(Resources::BlockType::Air);
                    }
                }
            }
        }
    }


    /**
     * Adds the blocks to the chunk mesh
     */
    void Chunk::addBlocksToChunkMesh() {
        // Data storage of vertices and indices
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        GLuint indexOffset = 0;
        for (int x = 0; x < m_blocks.getX(); x++) {
            for (int y = 0; y < m_blocks.getY(); y++) {
                for (int z = 0; z < m_blocks.getZ(); z++) {
                    BlockModel& block = m_blocks(x, y, z);
                    if (block.getBlockType() != Resources::BlockType::Air) {
                        glm::vec3 position = glm::vec3(x, y, z);
                        std::array<bool, 6> neighbours = getBlockNeighbours(position);
                        block.addToMesh(position, neighbours, vertices, indices, indexOffset);
                    }
                }
            }
        }

        // Generate the VAO, VBO and EBO
        {
            // Generate the VAO, VBO and EBO
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            // Bind the VAO
            glBindVertexArray(m_VAO);
            CHECK_IF_GL_ERROR("Error in binding VAO");

            // VBO: Store the vertices
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

            // EBO: Store the indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

            // Set up the vertex attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)nullptr); // Position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Texture Coords
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat))); // Texture Array Index
            glEnableVertexAttribArray(2);

            m_indexCount = indices.size();
            glBindVertexArray(0);
        }
    }


    std::array<bool, 6> Chunk::getBlockNeighbours(glm::vec3 blockPosition) {
        // So basically a block has 6 faces and therefore 6 neighbours
        // so we check the positions: +x, -x, +y, -y, +z, -z
        std::array<bool, 6> neighbours;
        neighbours.fill(false);

        enum NeighbourDirection { BOTTOM, TOP, LEFT, RIGHT, BACK, FRONT };

        // Sadly we have to use if statements here, because we can't use a loop, it would be significantly slower
        // Neighbour +x
        if (blockPosition.x + 1 < m_blocks.getX()) {
            BlockModel& neighbour = m_blocks(blockPosition.x + 1, blockPosition.y, blockPosition.z);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[RIGHT] = true;
            }
        }
        // Neighbour -x
        if (blockPosition.x - 1 >= 0) {
            BlockModel& neighbour = m_blocks(blockPosition.x - 1, blockPosition.y, blockPosition.z);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[LEFT] = true;
            }
        }
        // Neighbour +y
        if (blockPosition.y + 1 < m_blocks.getY()) {
            BlockModel& neighbour = m_blocks(blockPosition.x, blockPosition.y + 1, blockPosition.z);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[TOP] = true;
            }
        }
        // Neighbour -y
        if (blockPosition.y - 1 >= 0) {
            BlockModel& neighbour = m_blocks(blockPosition.x, blockPosition.y - 1, blockPosition.z);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[BOTTOM] = true;
            }
        }
        // Neighbour +z
        if (blockPosition.z + 1 < m_blocks.getZ()) {
            BlockModel& neighbour = m_blocks(blockPosition.x, blockPosition.y, blockPosition.z + 1);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[FRONT] = true;
            }
        }
        // Neighbour -z
        if (blockPosition.z - 1 >= 0) {
            BlockModel& neighbour = m_blocks(blockPosition.x, blockPosition.y, blockPosition.z - 1);
            if (neighbour.getBlockType() != Resources::BlockType::Air) {
                neighbours[BACK] = true;
            }
        }

        return neighbours;
    }


    /**
     * Render the chunk
     * @param blockShader
     */
    void Chunk::render(Shader* blockShader) {
        blockShader->use();

        // Check if the block is visible from the camera
        Camera* camera = Player::getInstance()->getCamera();

        // Translate the block
        auto model = glm::mat4(1.0f);
        model = rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::vec3 chunkPosition = glm::vec3(m_position.first, 0, m_position.second);
        model = translate(model, chunkPosition);

        // Get the camera position
        glm::vec3 cameraPos = camera->getPosition();
        glm::vec3 cameraFront = camera->getFront();
        glm::vec3 cameraUp = camera->getUp();

        auto view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        auto projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);

        blockShader->setMat4("model", model);
        blockShader->setMat4("view", view);
        blockShader->setMat4("projection", projection);

        // bind texture array
        glActiveTexture(GL_TEXTURE0);
        GLuint textureArrayId = Resources::TextureLoader::getInstance()->getTextureArrayId();
        glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayId);
        blockShader->setInt("ourTextureArray", 0);
        CHECK_IF_GL_ERROR("Error in binding texture array");

        // render the chunk
        glBindVertexArray(m_VAO);
        CHECK_IF_GL_ERROR("Error in binding VAO");
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
} // Minecraft