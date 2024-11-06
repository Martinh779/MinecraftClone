//
// Created by Martin Hertel on 29.07.2024.
//

#include "Logger.h"
#include "glad/glad.h"
#include <iostream>

namespace GL {
    void Logger::errorCheck() {
        GLenum err;
        if((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: "  << errorMap[err] << std::endl;
        }
    }

    void Logger::errorCheck(const char* file, int line, const char* message) {
        GLenum err;
        if((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: "  << errorMap[err] << " in file " << file << " at line " << line << std::endl
                      << "  Message: " << message << std::endl;
        }
    }
} // GL