/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>

namespace Physics {
    struct BoundingBox {
        glm::vec3 min;
        glm::vec3 max;

        BoundingBox() : min(glm::vec3(0.0f)), max(glm::vec3(0.0f)) {}
        BoundingBox(const glm::vec3& min, const glm::vec3& max) : min(min), max(max) {}

        void setMinMax(const glm::vec3& min, const glm::vec3& max) {
            this->min = min;
            this->max = max;
        }

        [[nodiscard]] float overlap(const BoundingBox& other, int axis) const {
            return std::max(0.0f, std::min(max[axis], other.max[axis]) - std::max(min[axis], other.min[axis]));
        }

        [[nodiscard]] bool isAABBOverlapping(const BoundingBox& other) const {
            return min.x <= other.max.x && max.x >= other.min.x &&
                   min.y <= other.max.y && max.y >= other.min.y &&
                   min.z <= other.max.z && max.z >= other.min.z;
        }

        [[nodiscard]] bool isAABBOverlapping(std::vector<BoundingBox> b) const {
            for (auto& box : b) {
                if (isAABBOverlapping(box)) {
                    return true;
                }
            }
            return false;
        }
    };
} // Physics

#endif //BOUNDINGBOX_H
