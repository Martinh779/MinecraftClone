/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "Player.h"

#include "../Physics/Collision.h"
#include "../World/Chunk.h"
#include "../Utils/ConfigLoader.h"
#include "../Utils/Logger.h"

namespace Minecraft {

    Player* Player::m_instance = nullptr;


    Player::Player() {
        // Load config
        Utils::ConfigLoader* configLoader = Utils::ConfigLoader::getInstance();
        m_speed = configLoader->getCameraSpeed();
        m_sensitivity = configLoader->getCameraSensitivity();

        m_moveForwardKey = configLoader->getForwardKey();
        m_moveBackwardKey = configLoader->getBackwardKey();
        m_moveLeftKey = configLoader->getLeftKey();
        m_moveRightKey = configLoader->getRightKey();
        m_jumpKey = configLoader->getJumpKey();
        m_crouchKey = configLoader->getCrouchKey();

        m_camera = Camera(m_sensitivity);
    }


    Player::~Player() = default;


    Player* Player::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Player();
        }
        return m_instance;
    }


    void Player::updateCameraVectors() {
        m_camera.updateCameraVectors(m_position + glm::vec3(0.0f, m_eyeHeight, 0.0f));
    }


    Camera* Player::getCamera() {
        return &m_camera;
    }


    Physics::BoundingBox Player::getBoundingBox() {
        return {m_position, m_position + glm::vec3(1.0f, m_eyeHeight, 1.0f)};
    }



    glm::vec3 Player::getPosition() {
        return m_position;
    }


    glm::vec3 Player::getChunkPosition() {
        glm::vec3 pos = getPosition();
        pos.x = std::floor(pos.x / Chunk::chunkSize[0]) * Chunk::chunkSize[0];
        pos.z = std::floor(pos.z / Chunk::chunkSize[2]) * Chunk::chunkSize[2];
        return pos;
    }


    void Player::setPosition(glm::vec3 newPos) {
        m_position = newPos;
    }


    void Player::addGravity() {
        glm::vec3 downwardMovement = glm::vec3(0.0f, -m_gravity, 0.0f);
        Physics::BoundingBox newBox = getBoundingBox();
        newBox.min += downwardMovement;
        newBox.max += downwardMovement;

        if (!newBox.isAABBOverlapping(Physics::Collision::getCollidingBoundingBoxes(*this))) {
            m_position += downwardMovement;
        } else {
            m_position.y = std::max(m_position.y, newBox.min.y);
        }
    }


    void Player::update(GLFWwindow *window) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        processInput(window);

        //addGravity();

        //Physics::Collision::checkPlayerCollision(*this);

        updateCameraVectors();
    }


    void Player::processInput(GLFWwindow *window) {
        // Close the window if the ESC key is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glm::vec3 front = m_camera.getFront();
        glm::vec3 up = m_camera.getUp();
        glm::vec3 right = m_camera.getRight();

        glm::vec3 newPos = m_position;

        // Walking
        if (glfwGetKey(window, m_moveForwardKey) == GLFW_PRESS) {
            newPos += glm::vec3(front.x, 0.0f, front.z) * m_speed;
        }
        if (glfwGetKey(window, m_moveBackwardKey) == GLFW_PRESS) {
            newPos -= glm::vec3(front.x, 0.0f, front.z) * m_speed;
        }
        if (glfwGetKey(window, m_moveLeftKey) == GLFW_PRESS) {
            newPos -= glm::vec3(right.x, 0.0f, right.z) * m_speed;
        }
        if (glfwGetKey(window, m_moveRightKey) == GLFW_PRESS) {
            newPos += glm::vec3(right.x, 0.0f, right.z) * m_speed;
        }
        if (glfwGetKey(window, m_jumpKey) == GLFW_PRESS) {
            newPos += up * m_speed;
        }
        if (glfwGetKey(window, m_crouchKey) == GLFW_PRESS) {
            newPos -= up * m_speed;
        }

        setPosition(newPos);

        // Mouse movement
        mouseCallback(window);
    }
    void Player::mouseCallback(GLFWwindow *window) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        getCamera()->processMouseMovement(xOffset, yOffset);
    }
} // Minecraft