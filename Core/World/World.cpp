//
// Created by Martin Hertel on 28.07.2024.
//

#include "World.h"

namespace Minecraft {
    World::World() {
        generateWorld();
    }


    void World::generateWorld() {
        // Create a BlockModel instance and get its m_vertices and m_indices
        chunk.generateChunk();
    }


    void World::renderWorld() {
        //testBlock.render(&m_blockShader);

        chunk.render(&m_blockShader);
    }
}
