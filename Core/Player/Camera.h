//
// Created by Martin Hertel on 03.08.2024.
//

#ifndef MINECRAFTCLONE_CAMERA_H
#define MINECRAFTCLONE_CAMERA_H

#include "glm/vec3.hpp"
#include "GLFW/glfw3.h"

namespace Minecraft {

    class Camera {
    private:
        // Singleton m_instance
        static Camera* m_instance;

    public:
        static Camera* getInstance();

        void update(GLFWwindow *window);
        void processInput(GLFWwindow *window);

        glm::vec3 getPosition();
        glm::vec3 getFront();
        glm::vec3 getRight();
        glm::vec3 getUp();

        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;

        Camera();
        ~Camera();

    private:
        void mouseCallback(GLFWwindow *window);

        // Camera attributes
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

        float yaw = -90.0f;
        float pitch = 0.0f;
        float speed = 0.5f;
        float sensitivity = 0.1f;

        // Mouse input
        bool firstMouse = true;

        double lastX = 0.0;
        double lastY = 0.0;

        GLuint m_moveForwardKey = GLFW_KEY_W;
        GLuint m_moveBackwardKey = GLFW_KEY_S;
        GLuint m_moveLeftKey = GLFW_KEY_A;
        GLuint m_moveRightKey = GLFW_KEY_D;
        GLuint m_jumpKey = GLFW_KEY_SPACE;
        GLuint m_crouchKey = GLFW_KEY_LEFT_CONTROL;
    };

} // Minecraft

#endif //MINECRAFTCLONE_CAMERA_H
