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
        void processInput(GLFWwindow *window);
    };
} // Minecraft
#endif //MINECRAFTCLONE_GAME_H
