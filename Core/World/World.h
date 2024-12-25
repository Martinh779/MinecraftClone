//
// Created by Martin Hertel on 28.07.2024.
//

#ifndef MINECRAFTCLONE_WORLD_H
#define MINECRAFTCLONE_WORLD_H


#include "BlockModel.h"
#include "../Rendering/Shader.h"
#include "Chunk.h"
#include <vector>

#include "../Utils/ChunkPosition.h"

#define CHUNK_COUNT 4

namespace Minecraft {
    class Player;
}

namespace Minecraft {

    class World {

    public:
        World();

        void generateWorld();

        void initChunks();

        void renderWorld();

    private:
        Player* m_player;
        Shader m_blockShader = Shader(R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Vertex.vs)",
                                    R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Fragment.fs)");

        // The chunks that are in the world
        std::unordered_map<std::pair<int, int>, std::shared_ptr<Chunk>, ChunkPositionHash> m_chunks;
        void generateAndRenderChunk();
        int m_renderDistance = 1; // In chunks
    };
} // Minecraft
#endif //MINECRAFTCLONE_WORLD_H
