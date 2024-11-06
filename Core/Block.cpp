//
// Created by herte on 09.02.2024.
//

#include "Block.h"

namespace Minecraft {

    const BlockType Block::BlocksRequiringBlockUnder[] = {
            BlockType::Cactus,
            BlockType::Poppy,
    };


    const BlockType Block::NonCollidableBlocks[] = {
            BlockType::Poppy,
    };


    /**
     * Whether or not the block needs a block under it, e.g. cactus
     * @return
     */
    bool Block::NeedsBlockUnder() const {
        for (const auto& blockType : BlocksRequiringBlockUnder) {
            if (ActiveBlockType == blockType) {
                return true;
            }
        }
        return false;
    }


    bool Block::IsCollidable() const {
        for (const auto& blockType : NonCollidableBlocks) {
            if (ActiveBlockType == blockType) {
                return true;
            }
        }
        return false;
    }
} // Minecraft