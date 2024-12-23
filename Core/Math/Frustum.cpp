//
// Created by Martin Hertel on 15.11.2024.
//

#include "Frustum.h"
#include "../Player/Camera.h"
#include "Plane.h"
#include <initializer_list>

namespace Math {

    /**
    * Creates a frustum from a camera.
    * @param aspect The aspect ratio of the camera.
    * @param fovY The field of view of the camera.
    * @param zNear The near plane of the camera.
    * @param zFar The far plane of the camera.
    * @return The frustum created from the camera.
    */
    void Frustum::createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar) {
        Minecraft::Camera* camera = Minecraft::Camera::getInstance();

        const float halfVSide = zFar * tanf(fovY / 0.5f);
        const float halfHSide = halfVSide * aspect;
        const glm::vec3 frontMultFar = zFar * camera->getFront();

        nearFace = { camera->getPosition() + zNear * camera->getFront(), camera->getFront() };
        farFace = { camera->getPosition() + frontMultFar, -camera->getFront() };
        rightFace = { camera->getPosition(),
                              glm::cross(frontMultFar - camera->getRight() * halfHSide, camera->getUp()) };
        leftFace = { camera->getPosition(),
                             glm::cross(camera->getUp(),frontMultFar + camera->getRight() * halfHSide) };
        topFace = { camera->getPosition(),
                            glm::cross(camera->getRight(), frontMultFar - camera->getUp() * halfVSide) };
        bottomFace = { camera->getPosition(),
                               glm::cross(frontMultFar + camera->getUp() * halfVSide, camera->getRight()) };
    }


    /**
     * Check if a box is in the frustum
     * @param min The minimum point of the box
     * @param max The maximum point of the box
     * @return True if the box is in the frustum, false otherwise
     */
    bool Frustum::isBoxInFrustum(const glm::vec3& min, const glm::vec3& max) {
        for (const Plane &plane: {topFace, bottomFace, leftFace, rightFace, nearFace, farFace}) {
            glm::vec3 positiveVertex = min;
            glm::vec3 negativeVertex = max;

            if (plane.normal.x >= 0) {
                positiveVertex.x = max.x;
                negativeVertex.x = min.x;
            }
            if (plane.normal.y >= 0) {
                positiveVertex.y = max.y;
                negativeVertex.y = min.y;
            }
            if (plane.normal.z >= 0) {
                positiveVertex.z = max.z;
                negativeVertex.z = min.z;
            }

            if (glm::dot(plane.normal, negativeVertex - plane.distance) > 0) {
                return false;
            }
        }
        return true;
    }
} // Math