//
// Created by Martin Hertel on 03.08.2024.
//

#ifndef MINECRAFTCLONE_CAMERA_H
#define MINECRAFTCLONE_CAMERA_H

#include "glm/vec3.hpp"
#include "GLFW/glfw3.h"

namespace Minecraft {

    class Camera {
    public:
        static Camera &getInstance();

        void update(GLFWwindow *window);
        void processInput(GLFWwindow *window);

        glm::vec3 getPosition();
        glm::vec3 getFront();
        glm::vec3 getRight();
        glm::vec3 getUp();

        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;

        Camera() = default;
        ~Camera() = default;

    private:
        static void mouseCallback(GLFWwindow *window, double x_pos, double y_pos);

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        float yaw = -90.0f;
        float pitch = 0.0f;
        float speed = 0.05f;
        float sensitivity = 0.1f;
        float fov = 45.0f;
    };

} // Minecraft

#endif //MINECRAFTCLONE_CAMERA_H
