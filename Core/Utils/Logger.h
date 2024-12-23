//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_LOGGER_H
#define MINECRAFTCLONE_LOGGER_H

#include <cstdarg>
#include <map>
#include <string>
#include "glad/glad.h"
#include "glm/vec3.hpp"

#define CHECK_IF_GL_ERROR(message) Utils::Logger::glErrorCheck(__FILE__, __LINE__, message)
#define CHECK_VECTOR(message, vector) Utils::Logger::vectorCheck(message, vector)
#define LOG(message, type, arg) Utils::Logger::log(message, type, (arg))

#define LOG_INFO Utils::LogType::INFO
#define LOG_WARNING Utils::LogType::WARNING
#define LOG_ERROR Utils::LogType::ERROR

namespace Utils {

    enum class LogType {
        INFO,
        WARNING,
        ERROR,
    };

    class Logger {
    public:
        static void glErrorCheck(const char* file, int line, const char* message);

        static void vectorCheck(const char* message, const glm::vec3 &vector);

        template<typename... Args>
        static void log(const char* message, LogType type, Args... args);

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

} // Utils

#endif //MINECRAFTCLONE_LOGGER_H
