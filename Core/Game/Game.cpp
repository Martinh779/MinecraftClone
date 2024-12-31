/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "Game.h"
#include "../Utils/Logger.h"
#include "../Player/Player.h"
#include "../World/World.h"
#include <iostream>

#include "../Utils/ConfigLoader.h"

namespace Minecraft {
    Game::Game() {
        Utils::ConfigLoader* configLoader = Utils::ConfigLoader::getInstance();
        m_screenWidth = configLoader->getScreenWidth();
        m_screenHeight = configLoader->getScreenHeight();
        LOG(LOG_INFO, "Game created");
    }

    int Game::handleWindow() {
        // Initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFW window
        GLFWwindow *window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Minecraft", nullptr, nullptr);
        if (window == nullptr) {
            LOG(LOG_ERROR, "Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // Load all OpenGL function pointers using GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            LOG(LOG_ERROR, "Failed to initialize GLAD");
            return -1;
        }

        Player* player = Player::getInstance();
        World* world = World::getInstance();

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Render loop
        while (!glfwWindowShouldClose(window)) {
            // Enable depth testing
            glEnable(GL_DEPTH_TEST);

            // Enable face culling
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);

            // Process input
            player->update(window);

            // Clear the screen
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render the world
            world->update();

            //updateFPS();

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Terminate GLFW
        glfwTerminate();
        return 0;
    }


    void Game::processInput(GLFWwindow *window) {
        // Close the window if the ESC key is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }


    void Game::updateFPS() {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        LOG(LOG_INFO, ("FPS: " + std::to_string(1.0f / deltaTime)).c_str());
    }

}
