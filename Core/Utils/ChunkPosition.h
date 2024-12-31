/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

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
