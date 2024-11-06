//
// Created by Martin Hertel on 10.02.2024.
//

#include <iostream>
#include "BlockModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "../stb_image.h"
#include "../Utils/Logger.h"
#include "../Player/Camera.h"
#include "../Player/Player.h"


namespace Minecraft {

    BlockModel::BlockModel() {
        m_vertices = {
                // positions          // texture coords
                // Bottom Face
                0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // front top left
                1.0f, 1.0f, 0.0f,    1.0f, 1.0f, // front top right
                0.0f, 0.0f, 0.0f,    0.0f, 0.0f, // front bottom left
                1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // front bottom right

                // Top Face
                0.0f, 1.0f, 1.0f,    1.0f, 1.0f, // back top left
                1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // back top right
                0.0f, 0.0f, 1.0f,    1.0f, 0.0f, // back bottom left
                1.0f, 0.0f, 1.0f,    0.0f, 0.0f, // back bottom right

                // Left Face
                0.0f, 1.0f, 1.0f,    1.0f, 1.0f, // back top left
                0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // front top left
                0.0f, 0.0f, 1.0f,    0.0f, 1.0f, // back bottom left
                0.0f, 0.0f, 0.0f,    0.0f, 0.0f, // front bottom left

                // Right Face
                1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // front top right
                1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // back top right
                1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // front bottom right
                1.0f, 0.0f, 1.0f,    1.0f, 1.0f, // back bottom right

                // Back Face
                0.0f, 1.0f, 1.0f,    0.0f, 1.0f, // back top left
                1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // back top right
                0.0f, 1.0f, 0.0f,    0.0f, 0.0f, // front top left
                1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // front top right

                // Front Face
                0.0f, 0.0f, 0.0f,    0.0f, 0.0f, // front bottom left
                1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // front bottom right
                0.0f, 0.0f, 1.0f,    0.0f, 1.0f, // back bottom left
                1.0f, 0.0f, 1.0f,    1.0f, 1.0f  // back bottom right
        };

        m_indices = {
                // Bottom Face
                0, 1, 2,
                1, 3, 2,

                // Top Face
                4, 6, 5,
                6, 7, 5,

                // Front Face
                8, 9, 10,
                9, 11, 10,

                // Right Face
                12, 13, 14,
                13, 15, 14,

                // Back Face
                16, 17, 18,
                17, 19, 18,

                // Left Face
                20, 21, 22,
                21, 23, 22
        };
        size_t verticesLen = m_vertices.size() * sizeof(GL_FLOAT);
        size_t indicesLen = m_indices.size() * sizeof(GL_UNSIGNED_INT);

        // Bind buffers and arrays
        m_VAO.bind();
        m_VBO.bind();
        m_EBO.bind();

        // Copy vertex data to the buffer
        m_VBO.bufferData(verticesLen, &m_vertices[0], GL_STATIC_DRAW);
        m_EBO.bufferData(indicesLen, &m_indices[0], GL_STATIC_DRAW);

        // Set the vertex attribute pointers
        m_VAO.setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        m_VAO.setAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

        // Unbind the buffers
        m_VAO.unbind();
        m_VBO.unbind();
        m_EBO.unbind();

        m_top_textureID = loadTexture(BlockTextures.at(ActiveBlockType).topTexturePath);
        m_side_textureID = loadTexture(BlockTextures.at(ActiveBlockType).sideTexturePath);
        m_bottom_textureID = loadTexture(BlockTextures.at(ActiveBlockType).bottomTexturePath);
    }


    const std::vector<float> BlockModel::getVertices() const {
        return m_vertices;
    }


    const std::vector<unsigned int> BlockModel::getIndices() const {
        return m_indices;
    }


    GLuint BlockModel::loadTexture(const char* path) {
        // Load texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels,
                                        0);

        if (data) {
            if (nrChannels == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else if (nrChannels == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            } else {
                std::cout << "Failed to load texture: " << path << std::endl;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture: " << path << std::endl;
        }
        stbi_image_free(data);
        std::cout << "Successfully loaded texture: " << path << std::endl;

        return textureID;
    }


    void BlockModel::setBlockType(BlockType blockType) {
        ActiveBlockType = blockType;
    }


    void BlockModel::render(Shader *shader, glm::vec3 position) {
        // Check if the block is visible from the camera
        Camera* camera = Camera::getInstance();


        // Translate the block
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, position);



        // Get the camera position
        glm::vec3 cameraPos = camera->getPosition();
        glm::vec3 cameraFront = camera->getFront();
        glm::vec3 cameraUp = camera->getUp();

        // View matrix
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // Projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        shader->use();

        unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        m_VAO.bind();
        // Draw bottom face
        glBindTexture(GL_TEXTURE_2D, m_bottom_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));

        // Draw top face
        glBindTexture(GL_TEXTURE_2D, m_top_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));

        // Draw left face
        glBindTexture(GL_TEXTURE_2D, m_side_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));

        // Draw right face
        glBindTexture(GL_TEXTURE_2D, m_side_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));

        // Draw back face
        glBindTexture(GL_TEXTURE_2D, m_side_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));

        // Draw front face
        glBindTexture(GL_TEXTURE_2D, m_side_textureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint)));

        //checkIfError("Failed to draw elements");
        m_VAO.unbind();
    }


    BlockModel::~BlockModel() {
        std::cout << "Deleted BlockModel" << std::endl;
    }
} // Minecraft