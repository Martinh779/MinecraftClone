//
// Created by Martin Hertel on 10.02.2024.
//

#ifndef MINECRAFTCLONE_BLOCKMODEL_H
#define MINECRAFTCLONE_BLOCKMODEL_H

#include <vector>
#include "glad/glad.h"
#include "../Rendering/Shader.h"
#include "glm/vec3.hpp"
#include "../Assets/TextureLoader.h"


namespace Minecraft {

    class BlockModel {
    public:
        BlockModel();
        ~BlockModel();

        void render(Shader* shader, glm::vec3 position);

        void setBlockType(Resources::BlockType blockType);
        Resources::BlockType getBlockType() const { return m_blockType; }

        glm::vec3 getPosition() const { return m_position; }
        void setPosition(glm::vec3 position);

        void addToMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, GLuint& indexOffset);

    protected:
        bool bIsInvisible = false;
        Resources::BlockType m_blockType;

    private:
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        glm::vec3 m_position;

        struct Resources::BlockTextureLayer m_blockTextureLayer{};
    };
} // Minecraft
#endif //MINECRAFTCLONE_BLOCKMODEL_H
