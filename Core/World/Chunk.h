/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

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

        // Get the block at the specified position in local coordinates
        [[nodiscard]] BlockModel* getBlockAt(int x, int y, int z) { return &m_blocks(x, y, z); }

        void setPosition(std::pair<int, int> position) { m_position = position; }

        void addBlocksToChunkMesh();

        void render(Shader* blockShader);

        constexpr static int chunkSize[3] = {16, 256, 16};

        [[nodiscard]] std::pair<int, int> getPosition() const { return m_position; }

        std::array<bool, 6> getBlockNeighbours(glm::vec3 blockPosition);

        // TODO: Add a method to recalculate the chunk, in case something changed

    private:
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
