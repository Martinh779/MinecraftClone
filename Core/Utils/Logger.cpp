/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "Logger.h"

#include <iomanip>

#include "glad/glad.h"
#include <iostream>
#include <sstream>

namespace Utils {

    void Logger::initialize(const std::string &logFileBaseName) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);

        std::ostringstream timestamp;
        timestamp << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        std::string logFileName = logFileBaseName + "_" + timestamp.str() + ".log";

        logFileStream.open(logFileName, std::ios::out | std::ios::trunc);
        if (!logFileStream.is_open()) {
            std::cerr << "[ERROR] Could not open log file: " << logFileName << std::endl;
        }
    }


    void Logger::cleanup() {
        if (logFileStream.is_open()) {
            logFileStream.close();
        }
    }



    void Logger::glErrorCheck(const char* file, int line, const char* message) {
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: "  << errorMap[err] << " in file " << file << " at line " << line << std::endl
                      << "  Message: " << message << std::endl;
        }
    }


    void Logger::vectorCheck(const char* message, const glm::vec3 &vector) {
        std::cout << message << ": " << vector.x << ", " << vector.y << ", " << vector.z << std::endl;
    }

} // Utils