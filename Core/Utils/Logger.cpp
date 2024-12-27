//
// Created by Martin Hertel on 29.07.2024.
//

#include "Logger.h"

#include "glad/glad.h"
#include <iostream>

namespace Utils {

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