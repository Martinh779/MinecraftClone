//
// Created by Martin Hertel on 09.02.2024.
//

#ifndef MINECRAFTCLONE_BLOCK_H
#define MINECRAFTCLONE_BLOCK_H

#include <iostream>
#include "Rendering/BlockModel.h"

namespace Minecraft {

    class Block : public BlockModel {

    public:
        bool NeedsBlockUnder() const;
        bool IsCollidable() const;

    private:
        static const BlockType BlocksRequiringBlockUnder[];
        static const BlockType NonCollidableBlocks[];

    };

} // Minecraft

#endif //MINECRAFTCLONE_BLOCK_H
