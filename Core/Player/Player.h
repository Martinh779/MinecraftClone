/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_PLAYER_H
#define MINECRAFTCLONE_PLAYER_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../Physics/BoundingBox.h"

namespace Minecraft {

    class Player {
    public:
        static Player* getInstance();

        Player();
        ~Player();

        Camera* getCamera();

        [[nodiscard]] Physics::BoundingBox getBoundingBox();

        void update(GLFWwindow *window);

        void updateCameraVectors();

        void processInput(GLFWwindow *window);

        glm::vec3 getPosition();
        glm::vec3 getChunkPosition();

        // Needed for collision handling
        void setPosition(glm::vec3 newPos);

        void addGravity();

    private:
        static Player* m_instance;

        Camera m_camera;

        int m_eyeHeight = 2;
        float m_sensitivity = 0.1;

        void mouseCallback(GLFWwindow *window);

        // Camera attributes
        glm::vec3 m_position = glm::vec3(0.0f, 200.0f, 0.0f);

        float m_speed = 0.5f;

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

        float m_gravity = 0.02f;
    };

} // Minecraft

#endif //MINECRAFTCLONE_PLAYER_H
