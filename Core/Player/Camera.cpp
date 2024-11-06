//
// Created by Martin Hertel on 03.08.2024.
//

#include <iostream>
#include "Camera.h"

namespace Minecraft {

        Camera &Camera::getInstance() {
            static Camera instance;
            return instance;
        }


        void Camera::update(GLFWwindow *window) {
            processInput(window);
        }


        void Camera::processInput(GLFWwindow *window) {
            // Walking
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                position += front * speed;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                position -= front * speed;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                position -= right * speed;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                position += right * speed;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                position += up * speed;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                position -= up * speed;
            }

            // Mouse movement

        }


        void Camera::mouseCallback(GLFWwindow *window, double x_pos, double y_pos) {

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
} // Minecraft