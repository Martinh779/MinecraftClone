/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */


#include "World.h"

#include <chrono>

#include "../Physics/Collision.h"
#include "../Player/Player.h"
#include "../Utils/ConfigLoader.h"
#include "../Utils/Logger.h"

namespace Minecraft {

    World *World::m_instance = nullptr;


    World *World::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new World();
        }
        return m_instance;
    }


    /**
     * Constructor for the world
     */
    World::World() {
        Utils::ConfigLoader* configLoader = Utils::ConfigLoader::getInstance();
        m_renderDistance = configLoader->getChunkRenderDistance();

        m_renderDistance = m_renderDistance * Chunk::chunkSize[0];
        m_player = Player::getInstance();
        generateWorld();
    }


    /**
     * Get the block at the specified position
     * @param x The x position of the block
     * @param y The y position of the block
     * @param z The z position of the block
     * @return The block at the specified position
     */
    BlockModel *World::getBlockAt(int x, int y, int z) {
        // Get the chunk that the block is in
        int chunkX = x / Chunk::chunkSize[0] * Chunk::chunkSize[0];
        int chunkZ = z / Chunk::chunkSize[2] * Chunk::chunkSize[2];
        std::pair<int, int> pos = std::make_pair(chunkX, chunkZ  );

        if (auto chunk = m_chunks.at(pos)) {
            // getBlockAt expects the block position relative to the chunk so we need to mod the x and z values
            x = std::abs(x) % Chunk::chunkSize[0];
            y = glm::clamp(y, 0, Chunk::chunkSize[1] - 1);
            z = std::abs(z) % Chunk::chunkSize[2];

            return chunk->getBlockAt(x, y, z);
        }
        return nullptr;
    }


    /**
     * Generate the world
     */
    void World::generateWorld() {
        initChunks();
    }


    /**
     * Initialize the chunks
     */
    void World::initChunks() {
        for (int x = -m_renderDistance; x <= m_renderDistance; x += Chunk::chunkSize[0]) {
            for (int z = -m_renderDistance; z <= m_renderDistance; z += Chunk::chunkSize[2]) {
                std::pair<int, int> pos = std::make_pair(x, z);
                auto start = std::chrono::high_resolution_clock::now();
                auto chunk = std::make_shared<Chunk>(pos);
                auto end = std::chrono::high_resolution_clock::now();
                m_chunks.emplace(pos, chunk);
                LOG(LOG_INFO, "Chunk generated at position: {}, {} in {} ms", pos.first, pos.second,
                    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
            }
        }
    }


    /**
     * Render the world
     */
    void World::renderWorld() {
        generateAndRenderChunk();
    }


    /**
     * Generate and render the chunk
     */
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
                    LOG(LOG_ERROR, "Chunk at position: {}, {} is nullptr", pos.first, pos.second);
                }
            }
        }
    }


    void World::update() {
        // Render the world
        renderWorld();
    }

}
