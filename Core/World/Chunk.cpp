//
// Created by Martin Hertel on 29.07.2024.
//

#include "Chunk.h"

#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Math/PerlinNoise.h"
#include "../Utils/Logger.h"
#include "../Player/Camera.h"

namespace Minecraft {
    class Camera;

    /**
     * Default constructor
     */
    Chunk::Chunk(std::pair<int, int> position) {
        m_position = position;
        fillChunk();
        generateChunkPerlinNoise();
        LOG(LOG_INFO, "Chunk generated at position: {}, {}", m_position.first, m_position.second);
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
     * Fill the chunk with empty blocks
     */
    void Chunk::fillChunk() {
        for (int x = 0; x < chunkSize[0]; x++) {
            for (int z = 0; z < chunkSize[2]; z++) {
                for (int y = chunkSize[1] - 1; y >= 0; y--) {
                    BlockModel& block = m_blocks(x, y, z);
                    block.setBlockType(Resources::BlockType::Air);
                    block.setPosition(glm::vec3(x, y, z));
                }
            }
        }
    }


    /**
     * Generate the chunk with perlin noise
     */
    void Chunk::generateChunkPerlinNoise() {
        // The chunk will always be generated along the x and y-axis (positive) and the z axis as height
        Math::PerlinNoise* perlinNoise = Math::PerlinNoise::getInstance();

        // Data storage of vertices and indices
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        // Now replace air blocks with solid blocks, we iterate through each grid cell, and calculate the height of the terrain at that point
        GLuint indexOffset = 0;
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
                    if (block.getBlockType() != Resources::BlockType::Air) {
                        block.addToMesh(vertices, indices, indexOffset);
                    }
                }
            }
        }

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


    /**
     * Render the chunk
     * @param blockShader
     */
    void Chunk::render(Shader* blockShader) {
        blockShader->use();

        // Check if the block is visible from the camera
        Camera* camera = Camera::getInstance();

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