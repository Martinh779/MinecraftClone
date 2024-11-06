//
// Created by Martin Hertel on 05.08.2024.
//

#include "Transform.h"
#include "glm/ext/matrix_transform.hpp"

namespace Math {

    glm::mat4 Transform::getLocalModelMatrix() {
        const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                                                 glm::radians(m_rotation.x),
                                                 glm::vec3(1.0f, 0.0f, 0.0f));
        const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                                                 glm::radians(m_rotation.y),
                                                 glm::vec3(0.0f, 1.0f, 0.0f));
        const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                                                 glm::radians(m_rotation.z),
                                                 glm::vec3(0.0f, 0.0f, 1.0f));

        const glm::mat4 rotationMatrix = transformX * transformY * transformZ;

        return glm::translate(glm::mat4(1.0f), m_position) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
    }
}