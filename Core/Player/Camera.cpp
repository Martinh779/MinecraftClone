//
// Created by Martin Hertel on 03.08.2024.
//

#include <iostream>
#include "Camera.h"
#include "glm/trigonometric.hpp"
#include "glm/geometric.hpp"

namespace Minecraft {

    Camera* Camera::instance = nullptr;

    /**
     * Singleton instance
     */
    Camera* Camera::getInstance() {
        if (instance == nullptr) {
            instance = new Camera();
        }
        return instance;
    }


    /**
     * Updates the camera position and orientation
     * @param window The GLFW window
     */
    void Camera::update(GLFWwindow *window) {
        processInput(window);
    }


    /**
     * Processes input from the keyboard and mouse
     * @param window The GLFW window
     */
    void Camera::processInput(GLFWwindow *window) {
        // Walking
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position += front * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position -= front * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= glm::normalize(glm::cross(front, up)) * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += glm::normalize(glm::cross(front, up)) * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            position += up * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            position -= up * speed;
        }

        // Mouse movement
        mouseCallback(window);
    }


    /**
     * Processes mouse input
     * @param window The GLFW window
     */
    void Camera::mouseCallback(GLFWwindow *window) {
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        if (firstMouse) {
            lastX = x_pos;
            lastY = y_pos;
            firstMouse = false;
        }
        float x_offset = x_pos - lastX;
        float y_offset = lastY - y_pos;
        lastX = x_pos;
        lastY = y_pos;

        x_offset *= sensitivity;
        y_offset *= sensitivity;

        yaw += x_offset;
        pitch += y_offset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
    }


    glm::vec3 Camera::getPosition() {
        return position;
    }


    glm::vec3 Camera::getFront() {
        return front;
    }


    glm::vec3 Camera::getRight() {
        return right;
    }


    glm::vec3 Camera::getUp() {
        return up;
    }


    Camera::~Camera() {
        delete instance;
        instance = nullptr;
    }
} // Minecraft