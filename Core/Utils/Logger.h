/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_LOGGER_H
#define MINECRAFTCLONE_LOGGER_H

#include <cstdarg>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "glad/glad.h"
#include "glm/vec3.hpp"

#define CHECK_IF_GL_ERROR(message) Utils::Logger::glErrorCheck(__FILE__, __LINE__, message)
#define CHECK_VECTOR(message, vector) Utils::Logger::vectorCheck(message, vector)
#define LOG(type, message, ...) Utils::Logger::log(type, message, ##__VA_ARGS__)

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
        static void initialize(const std::string& logFileBaseName);

        static void cleanup();

        static void glErrorCheck(const char* file, int line, const char* message);

        static void vectorCheck(const char* message, const glm::vec3 &vector);

        template<typename... Args>
        static void log(LogType type, const char* message, Args... args) {
            std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
            std::string logPrefix;

            switch (type) {
                case LogType::INFO:
                    logPrefix = "[INFO] ";
                break;
                case LogType::WARNING:
                    logPrefix = "[WARNING] ";
                break;
                case LogType::ERROR:
                    logPrefix = "[ERROR] ";
                break;
            }
            std::string fullMessage = logPrefix + formattedMessage;

            if (type == LogType::ERROR) {
                std::cerr << fullMessage << std::endl;
            } else {
                std::cout << fullMessage << std::endl;
            }

            if (logFileStream.is_open()) {
                logFileStream << fullMessage << std::endl;
            }
        }

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

        inline static std::ofstream logFileStream;
    };

} // Utils

#endif //MINECRAFTCLONE_LOGGER_H
