//
// Created by Martin Hertel on 28.07.2024.
//

#ifndef MINECRAFTCLONE_WORLD_H
#define MINECRAFTCLONE_WORLD_H


#include "../Rendering/BlockModel.h"
#include "../Rendering/Shader.h"
#include "Chunk.h"
#include <vector>

namespace Minecraft {

    class World {

    public:
        World();

        void generateWorld();

        void renderWorld();

    private:
        //BlockModel testBlock;

        Chunk chunk;
        Shader m_blockShader = Shader("X:\\Programming\\Projects\\C\\MinecraftClone\\Core\\Shaders\\Block_Vertex.vs",
                                    "X:\\Programming\\Projects\\C\\MinecraftClone\\Core\\Shaders\\Block_Fragment.fs");
    };
} // Minecraft
#endif //MINECRAFTCLONE_WORLD_H
