//
// Created by Martin Hertel on 15.11.2024.
//

#include "Plane.h"
#include "glm/geometric.hpp"

namespace Math {

    Plane::Plane(const glm::vec3 &p1, const glm::vec3 &norm) : normal(glm::normalize(norm)), distance(glm::dot(normal, p1))
    {

    }
} // Math