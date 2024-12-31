/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_CAMERA_H
#define MINECRAFTCLONE_CAMERA_H

#include <glm/ext/quaternion_geometric.hpp>

#include "glm/vec3.hpp"
#include "GLFW/glfw3.h"

namespace Minecraft {

    class Camera {
    public:
        Camera(float sensitivity = 0.1f);

        void updateCameraVectors(glm::vec3 position);

        void processMouseMovement(float xOffset, float yOffset);

        glm::vec3 getPosition() { return m_position; }

        glm::vec3 getFront() { return m_front; }
        glm::vec3 getRight() { return glm::normalize(glm::cross(m_front, m_up)); }
        glm::vec3 getUp() { return m_up; }


    private:
        glm::vec3 m_position;
        glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);

        float m_yaw = -90.0f;
        float m_pitch = 0.0f;

        float m_sensitivity = 0.1f;
    };

} // Minecraft

#endif //MINECRAFTCLONE_CAMERA_H
