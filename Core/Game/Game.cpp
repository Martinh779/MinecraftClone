//
// Created by Martin Hertel on 09.02.2024.
//

#include "Game.h"
#include "../Utils/Logger.h"
#include "../Player/Player.h"
#include <iostream>

namespace Minecraft {
    int Game::handleWindow() {
        // Initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFW window
        GLFWwindow *window = glfwCreateWindow(1280, 720, "Minecraft", nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // Load all OpenGL function pointers using GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        Player* player = Player::getInstance();
        World world = World();

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
            world.renderWorld();

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
        std::cout << "FPS: " << (1 / deltaTime) << "/" << deltaTime << std::endl;
    }

}
