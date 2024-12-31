/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_WORLD_H
#define MINECRAFTCLONE_WORLD_H

#include "BlockModel.h"
#include "../Rendering/Shader.h"
#include "Chunk.h"
#include "../Utils/ChunkPosition.h"

#define CHUNK_COUNT 4

namespace Minecraft {
    class Player;
    class BlockModel;
    class Chunk;
}

namespace Minecraft {

    class World {

    public:
        static World* getInstance();

        World();

        BlockModel* getBlockAt(int x, int y, int z);

        void generateWorld();

        void initChunks();

        void renderWorld();

        void update();

    private:
        static World* m_instance;

        Player* m_player;
        Shader m_blockShader = Shader(R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Vertex.vs)",
                                    R"(G:\Programming\Projects\C\MinecraftClone\Core\Shaders\Block_Fragment.fs)");

        // The chunks that are in the world
        std::unordered_map<std::pair<int, int>, std::shared_ptr<Chunk>, ChunkPositionHash> m_chunks;
        void generateAndRenderChunk();
        int m_renderDistance = 3; // In chunks
    };
} // Minecraft
#endif //MINECRAFTCLONE_WORLD_H
