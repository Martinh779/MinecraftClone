//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_LOGGER_H
#define MINECRAFTCLONE_LOGGER_H

#include <map>
#include <string>
#include "glad/glad.h"

#define checkIfError(message) GL::Logger::errorCheck(__FILE__, __LINE__, message)

namespace GL {

    class Logger {
    public:
        static void errorCheck();

        static void errorCheck(const char* file, int line, const char* message);

    private:
        inline static std::map<GLenum, std::string> errorMap = {
                {GL_INVALID_ENUM, "GL_INVALID_ENUM"},
                {GL_INVALID_VALUE, "GL_INVALID_VALUE"},
                {GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
                {GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW"},
                {GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW"},
                {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
                {GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION"},
                {GL_CONTEXT_LOST, "GL_CONTEXT_LOST"},
        };
    };

} // GL

#endif //MINECRAFTCLONE_LOGGER_H
