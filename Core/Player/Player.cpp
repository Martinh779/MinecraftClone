//
// Created by Martin Hertel on 29.07.2024.
//

#include "Player.h"
#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"

namespace Minecraft {

    Player* Player::m_instance = nullptr;


    Player::Player() = default;


    Player::~Player() = default;


    Player* Player::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new Player();
        }
        return m_instance;
    }


    Camera* Player::getCamera() {
        return Camera::getInstance();
    }


    void Player::update(GLFWwindow *window) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        processInput(window);

        getCamera()->update(window);
    }


    void Player::processInput(GLFWwindow *window) {
        // Close the window if the ESC key is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
} // Minecraft