//
// Created by herte on 24.12.2024.
//

#ifndef CHUNKPOSITION_H
#define CHUNKPOSITION_H
#include <functional>

using ChunkPosition = std::pair<int, int>;

struct ChunkPositionHash {
    std::size_t operator()(const ChunkPosition& pos) const {
        return std::hash<int>()(pos.first) ^ std::hash<int>()(pos.second);
    }
};

#endif //CHUNKPOSITION_H
