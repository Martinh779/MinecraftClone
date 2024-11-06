//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_CHUNK_H
#define MINECRAFTCLONE_CHUNK_H

#include <array>
#include "../Block.h"
#include "../Rendering/BlockModel.h"

namespace Minecraft {

    class Chunk {
    public:
        Chunk();

        ~Chunk();

        BlockModel& getBlock(int x, int y, int z);

        void generateChunk();
        void render(Shader* blockShader);

    private:
        constexpr const static int chunkSize[3] = {16, 16, 5};
        BlockModel*** m_blocks;
    };

} // Minecraft

#endif //MINECRAFTCLONE_CHUNK_H
