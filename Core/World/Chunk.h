//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_CHUNK_H
#define MINECRAFTCLONE_CHUNK_H

#include <array>
#include "BlockModel.h"
#include "../Utils/BlockArray3D.h"


namespace Minecraft {

    class Chunk {
    public:
        Chunk(std::pair<int, int> position);

        ~Chunk();

        void setPosition(std::pair<int, int> position) { m_position = position; }

        void generateChunk();

        void generateChunkPerlinNoise();

        void render(Shader* blockShader);

        constexpr static int chunkSize[3] = {16, 256, 16};

        [[nodiscard]] std::pair<int, int> getPosition() const { return m_position; }

    private:
        //constexpr const static int chunkSize[3] = {8, 8, 256};
        //constexpr const static int chunkSize[3] = {1, 1, 1};
        Utils::BlockArray3D m_blocks = Utils::BlockArray3D(chunkSize[0], chunkSize[1], chunkSize[2]);

        GLuint m_VAO{};
        GLuint m_VBO{};
        GLuint m_EBO{};

        void fillChunk();

        std::pair<int, int> m_position{};
        unsigned int m_indexCount{};
    };

} // Minecraft

#endif //MINECRAFTCLONE_CHUNK_H
