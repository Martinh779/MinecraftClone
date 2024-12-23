//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_PLAYER_H
#define MINECRAFTCLONE_PLAYER_H

#include "GLFW/glfw3.h"
#include "Camera.h"

namespace Minecraft {

    class Player {
    public:
        static Player* getInstance();

        Player();
        ~Player();

        Camera* getCamera();

        void update(GLFWwindow *window);

        void processInput(GLFWwindow *window);

    private:
        static Player* m_instance;
    };

} // Minecraft

#endif //MINECRAFTCLONE_PLAYER_H
