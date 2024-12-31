/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_PLANE_H
#define MINECRAFTCLONE_PLANE_H

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

namespace Math {

    class Plane {
    public:
        Plane() = default;

        float getSignedDistanceToPlane(const glm::vec3& point) const
        {
            return glm::dot(normal, point) - distance;
        }

        glm::vec3 normal = {0.0f, 1.0f, 0.0f};

        Plane(const glm::vec3& p1, const glm::vec3& norm);

        float distance;
    };

} // Math

#endif //MINECRAFTCLONE_PLANE_H
