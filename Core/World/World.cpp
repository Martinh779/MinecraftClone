//
// Created by Martin Hertel on 28.07.2024.
//

#include "World.h"

namespace Minecraft {
    World::World() {
        m_chunks.reserve(CHUNK_COUNT * CHUNK_COUNT);
        generateWorld();
    }


    void World::generateWorld() {
        generateNewChunks();
    }

    void World::generateNewChunks() {
        for (int x = 0; x < CHUNK_COUNT; x++) {
            for (int z = 0; z < CHUNK_COUNT; z++) {
                m_chunks.emplace_back(glm::vec3(x * Chunk::chunkSize[0], 0, z * Chunk::chunkSize[2]));
            }
        }
    }


    void World::renderWorld() {
        for (auto& chunk : m_chunks) {
            chunk.render(&m_blockShader);
        }
    }
}
