//
// Created by Martin Hertel on 09.02.2024.
//

#ifndef MINECRAFTCLONE_GAME_H
#define MINECRAFTCLONE_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../World/World.h"

namespace Minecraft {
    class Game {

    public:
        int handleWindow();

    private:
        static void processInput(GLFWwindow *window);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        int frameCount = 0;
        int fps = 0.0f;

        void updateFPS();
    };
} // Minecraft
#endif //MINECRAFTCLONE_GAME_H
