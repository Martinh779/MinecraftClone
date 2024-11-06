//
// Created by Martin Hertel on 10.02.2024.
//

#ifndef MINECRAFTCLONE_BLOCKMODEL_H
#define MINECRAFTCLONE_BLOCKMODEL_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../GL/VertexBuffer.h"
#include "../GL/VertexArray.h"
#include "../GL/ElementBuffer.h"
#include "Shader.h"
#include <unordered_map>
#include "glm/vec3.hpp"


namespace Minecraft {

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

    struct BlockProperties {
        const char *topTexturePath;
        const char *sideTexturePath;
        const char *bottomTexturePath;
    };

    static const std::unordered_map<BlockType, BlockProperties> BlockTextures = {
            {BlockType::Grass, {
                "X:/Programming/Projects/C/MinecraftClone/Resources/textures/block/grass_block_top.png",
                "X:/Programming/Projects/C/MinecraftClone/Resources/textures/block/grass_block_side.png",
                "X:/Programming/Projects/C/MinecraftClone/Resources/textures/block/dirt.png"}},
    };

    class BlockModel {
    public:
        BlockModel();

        const std::vector<float> getVertices() const;
        const std::vector<unsigned int> getIndices() const;

        GLuint loadTexture(const char* path);

        void setBlockType(BlockType blockType);

        void render(Shader* shader, glm::vec3 position);

        ~BlockModel();

    private:
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        GL::VertexArray m_VAO;
        GL::VertexBuffer m_VBO;
        GL::ElementBuffer m_EBO;

        GLuint m_top_textureID;
        GLuint m_side_textureID;
        GLuint m_bottom_textureID;

    protected:
        BlockType ActiveBlockType = BlockType::Grass;
    };
} // Minecraft
#endif //MINECRAFTCLONE_BLOCKMODEL_H
