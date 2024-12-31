/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include <iostream>
#include "Camera.h"

#include "../Utils/ConfigLoader.h"
#include "glm/trigonometric.hpp"
#include "glm/geometric.hpp"

namespace Minecraft {

    Camera::Camera(float sensitivity) {
        m_sensitivity = sensitivity;
    }


    void Camera::updateCameraVectors(glm::vec3 position) {
        m_position = position;
    }


    void Camera::processMouseMovement(float xOffset, float yOffset) {
        xOffset *= m_sensitivity;
        yOffset *= m_sensitivity;

        m_yaw += xOffset;
        m_pitch += yOffset;

        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(direction);
    }

} // Minecraft