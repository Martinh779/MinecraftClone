//
// Created by Martin Hertel on 29.07.2024.
//

#include "Chunk.h"

namespace Minecraft {

    Chunk::Chunk() {
        m_blocks = new BlockModel**[chunkSize[0]];
        for (int i = 0; i < chunkSize[0]; i++) {
            m_blocks[i] = new BlockModel*[chunkSize[1]];
            for (int j = 0; j < chunkSize[1]; j++) {
                m_blocks[i][j] = new BlockModel[chunkSize[2]];
            }
        }
    }

    
    Chunk::~Chunk() {
        for (int i = 0; i < chunkSize[0]; i++) {
            for (int j = 0; j < chunkSize[1]; j++) {
                delete[] m_blocks[i][j];
            }
            delete[] m_blocks[i];
        }
        delete[] m_blocks;
    }


    BlockModel& Chunk::getBlock(int x, int y, int z) {
        if (x < 0 || x >= chunkSize[0] || y < 0 || y >= chunkSize[1] || z < 0 || z >= chunkSize[2]) {
            throw std::out_of_range("Block out of range");
        }
        return m_blocks[x][y][z];
    }


    void Chunk::generateChunk() {

    }


    void Chunk::render(Shader* blockShader) {
        for (int i = 0; i < chunkSize[0]; i++) {
            for (int j = 0; j < chunkSize[1]; j++) {
                for (int k = 0; k < chunkSize[2]; k++) {
                    m_blocks[i][j][k].render(blockShader, glm::vec3(i, j, -k));
                }
            }
        }
    }
} // Minecraft