//
// Created by Martin Hertel on 21.11.2024.
//

#ifndef MINECRAFTCLONE_BLOCKARRAY3D_H
#define MINECRAFTCLONE_BLOCKARRAY3D_H

#include <vector>
#include "../World/BlockModel.h"

namespace Utils {

    class BlockArray3D {
    public:
        BlockArray3D(int x, int y, int z) : m_x(x), m_y(y), m_z(z), m_blocks(x * y * z) {}

        Minecraft::BlockModel& operator()(int x, int y, int z) {
            return m_blocks[x * m_y * m_z + y * m_z + z];
        }

        [[nodiscard]] int getX() const { return m_x; }
        [[nodiscard]] int getY() const { return m_y; }
        [[nodiscard]] int getZ() const { return m_z; }

    private:
        int m_x;
        int m_y;
        int m_z;

        std::vector<Minecraft::BlockModel> m_blocks;
    };

} // Utils

#endif //MINECRAFTCLONE_BLOCKARRAY3D_H
