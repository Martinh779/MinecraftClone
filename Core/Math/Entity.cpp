//
// Created by Martin Hertel on 04.08.2024.
//

#include <cstdlib>
#include "Entity.h"
#include "../Player/Camera.h"
#include "glm/geometric.hpp"

namespace Math {

    /**
     * Creates a frustum from a camera.
     * @param aspect The aspect ratio of the camera.
     * @param fovY The field of view of the camera.
     * @param zNear The near plane of the camera.
     * @param zFar The far plane of the camera.
     * @return The frustum created from the camera.
     */
    Frustum createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar) {
        Minecraft::Camera& camera = Minecraft::Camera::getInstance();

        Frustum frustum;
        const float halfVSide = zFar * tanf(fovY / 0.5f);
        const float halfHSide = halfVSide * aspect;
        const glm::vec3 frontMultFar = zFar * camera.getFront();

        frustum.nearFace = { camera.getPosition() + zNear * camera.getFront(), camera.getFront() };
        frustum.farFace = { camera.getPosition() + frontMultFar, -camera.getFront() };
        frustum.rightFace = { camera.getPosition(),
                              glm::cross(frontMultFar - camera.getRight() * halfHSide, camera.getUp()) };
        frustum.leftFace = { camera.getPosition(),
                             glm::cross(camera.getUp(),frontMultFar + camera.getRight() * halfHSide) };
        frustum.topFace = { camera.getPosition(),
                            glm::cross(camera.getRight(), frontMultFar - camera.getUp() * halfVSide) };
        frustum.bottomFace = { camera.getPosition(),
                               glm::cross(frontMultFar + camera.getUp() * halfVSide, camera.getRight()) };

        return frustum;
    }

    Plane::Plane(const glm::vec3 &p1, const glm::vec3 &norm) : normal(glm::normalize(norm)), distance(glm::dot(normal, p1))
    {

    }
} // Math