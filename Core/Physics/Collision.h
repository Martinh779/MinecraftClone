/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef COLLISION_H
#define COLLISION_H
#include "../World/World.h"
#include "../Player/Player.h"

namespace Physics {
    class Collision {

    public:
        // Check if the player is colliding with any blocks in a 3x3x3 area around the player
        static std::vector<Physics::BoundingBox> getCollidingBoundingBoxes(Minecraft::Player& player);

        static void checkPlayerCollision(Minecraft::Player& player);
    };
}


#endif //COLLISION_H
