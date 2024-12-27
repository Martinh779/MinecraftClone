//
// Created by Martin Hertel on 28.07.2024.
//

#include "World.h"

#include <glm/detail/func_geometric.inl>

#include "../Player/Player.h"
#include "../Utils/ConfigLoader.h"

namespace Minecraft {
    World::World() {
        Utils::ConfigLoader* configLoader = Utils::ConfigLoader::getInstance();
        m_renderDistance = configLoader->getChunkRenderDistance();

        m_renderDistance = m_renderDistance * Chunk::chunkSize[0];
        m_player = Player::getInstance();
        generateWorld();
    }


    void World::generateWorld() {
        initChunks();
    }


    void World::initChunks() {
        // Init using render distance * 2 so the player can move in a direction seamlessly when the chunks are generated
        int multiplier = 2;
        int generateDistance = m_renderDistance * multiplier;
        for (int x = -generateDistance; x <= generateDistance; x += Chunk::chunkSize[0]) {
            for (int z = -generateDistance; z <= generateDistance; z += Chunk::chunkSize[2]) {
                std::pair<int, int> pos = std::make_pair(x, z);
                auto chunk = std::make_shared<Chunk>(pos);
                m_chunks.emplace(pos, chunk);
            }
        }
    }


    void World::renderWorld() {
        generateAndRenderChunk();
    }


    void World::generateAndRenderChunk() {
        // first thought would be to populate a vector2d with chunks that should be in render distance
        // each chunk that has its position in the vector2d would be rendered
        // rest of the positions in the vector would be generated
        glm::vec3 playerPos = m_player->getChunkPosition();
        for (int x = playerPos.x - m_renderDistance; x <= playerPos.x + m_renderDistance; x += Chunk::chunkSize[0]) {
            for (int z = playerPos.z - m_renderDistance; z <= playerPos.z + m_renderDistance;
                 z += Chunk::chunkSize[2]) {
                std::pair<int, int> pos = std::make_pair(x, z);
                // Create the chunk if it does not exist
                if (m_chunks.contains(pos) == false) {
                    auto chunk = std::make_shared<Chunk>(pos);
                    m_chunks.emplace(pos, chunk);
                }
                // Render the chunk
                auto chunk = m_chunks.at(pos);
                if (chunk != nullptr) {
                    chunk->render(&m_blockShader);
                } else {
                    std::cerr << "Chunk is nullptr" << std::endl;
                }
            }
        }
    }
}
