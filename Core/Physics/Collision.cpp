/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "Collision.h"

#include "../Utils/Logger.h"

namespace Physics {
    std::vector<Physics::BoundingBox> Collision::getCollidingBoundingBoxes(Minecraft::Player &player) {
        Minecraft::World* world = Minecraft::World::getInstance();
        std::vector<Physics::BoundingBox> collidingBoxes;
        glm::vec3 playerPos = player.getPosition();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    glm::ivec3 blockPos = glm::ivec3(playerPos.x + i - 1, playerPos.y + j - 1, playerPos.z + k - 1);

                    if (auto overlappingBlock = world->getBlockAt(blockPos.x, blockPos.y, blockPos.z)) {
                        if (overlappingBlock->getBlockType() == Resources::Air) {
                            continue;
                        }
                        Physics::BoundingBox blockBox = Physics::BoundingBox(blockPos, blockPos + glm::ivec3(1.0f));
                        if (player.getBoundingBox().isAABBOverlapping(blockBox)) {
                            collidingBoxes.push_back(blockBox);
                        }
                    }
                }
            }
        }
        if (collidingBoxes.size() > 0) {
            LOG_INFO("Colliding with " + std::to_string(collidingBoxes.size()) + " blocks");
            bool colliding = false;
        }

        return collidingBoxes;
    }


    void Physics::Collision::checkPlayerCollision(Minecraft::Player &player) {
        glm::vec3 playerPos = player.getPosition();
        Physics::BoundingBox playerBox = player.getBoundingBox();

        glm::vec3 totalAdjustment(0.0f);
        std::vector<Physics::BoundingBox> collidingBlocks = getCollidingBoundingBoxes(player);

        bool adjusted = true;
        int maxIterations = 10; // Safety limit to prevent infinite loop
        int iterationCount = 0;

        while (adjusted && iterationCount < maxIterations) {
            adjusted = false;
            glm::vec3 verticalAdjustment(0.0f);
            glm::vec3 horizontalAdjustment(0.0f);

            for (auto box : collidingBlocks) {
                glm::vec3 adjustment(0.0f);

                // Check for overlap in each axis
                for (int i = 0; i < 3; i++) {
                    float overlap = playerBox.overlap(box, i);
                    if (overlap > 0) {
                        float direction = playerPos[i] - box.min[i];
                        if (i == 1) { // y-axis (vertical adjustment)
                            if (direction > 0) {
                                verticalAdjustment.y = std::max(verticalAdjustment.y, overlap); // falling down
                            } else {
                                verticalAdjustment.y = std::min(verticalAdjustment.y, -overlap); // jumping or moving up
                            }
                        } else { // x and z axis (horizontal adjustments)
                            if (direction > 0) {
                                horizontalAdjustment.x = std::max(horizontalAdjustment.x, overlap);
                            } else {
                                horizontalAdjustment.x = std::min(horizontalAdjustment.x, -overlap);
                            }
                        }
                    }
                }
            }

            // Apply vertical and horizontal adjustments
            if (glm::length(verticalAdjustment) > 0.0f || glm::length(horizontalAdjustment) > 0.0f) {
                totalAdjustment = verticalAdjustment + horizontalAdjustment;
                player.setPosition(playerPos + totalAdjustment);

                // Check for new collisions after adjustment
                collidingBlocks = getCollidingBoundingBoxes(player);
                adjusted = !collidingBlocks.empty(); // If collisions still exist, continue adjusting
                iterationCount++; // Increment iteration count to avoid infinite loops
                LOG_INFO("Iteration: " + std::to_string(iterationCount) + " Adjusted: " + std::to_string(adjusted));
            }
        }

        if (iterationCount >= maxIterations) {
            LOG(LOG_WARNING, "Collision adjustment reached maximum iterations");
        }
    }
}
