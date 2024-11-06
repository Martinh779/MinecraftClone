//
// Created by Martin Hertel on 04.08.2024.
//

#ifndef MINECRAFTCLONE_ENTITY_H
#define MINECRAFTCLONE_ENTITY_H

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Transform.h"

namespace Math {

    struct Plane {
        glm::vec3 normal = {0.0f, 1.0f, 0.0f};
        float distance;

        Plane() = default;

        Plane(const glm::vec3& p1, const glm::vec3& norm);

        float getSignedDistanceToPlane(const glm::vec3& point) const
        {
            return glm::dot(normal, point) - distance;
        }
    };

    struct Frustum {
        Plane topFace;
        Plane bottomFace;

        Plane leftFace;
        Plane rightFace;

        Plane nearFace;
        Plane farFace;
    };

    struct Volume {
        virtual bool isOnFrustum(const Frustum& frustum, const Transform) const = 0;
    };

} // Math

#endif //MINECRAFTCLONE_ENTITY_H
