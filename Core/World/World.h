//
// Created by Martin Hertel on 28.07.2024.
//

#ifndef MINECRAFTCLONE_WORLD_H
#define MINECRAFTCLONE_WORLD_H


#include "BlockModel.h"
#include "../Rendering/Shader.h"
#include "Chunk.h"
#include <vector>

#define CHUNK_COUNT 4

namespace Minecraft {

    class World {

    public:
        World();

        void generateWorld();

        void renderWorld();

        void generateNewChunks();

    private:
        Shader m_blockShader = Shader(R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Vertex.vs)",
                                    R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Fragment.fs)");

        std::vector<Chunk> m_chunks;
    };
} // Minecraft
#endif //MINECRAFTCLONE_WORLD_H
