//
// Created by Martin Hertel on 29.07.2024.
//

#include "VertexArray.h"
#include "../Utils/Logger.h"
#include <iostream>

namespace GL {

        VertexArray::VertexArray() {
            glGenVertexArrays(1, &m_VAO);
            CHECK_IF_GL_ERROR("Failed to generate m_VAO");
        }

        VertexArray::~VertexArray() {
            glDeleteVertexArrays(1, &m_VAO);
        }

        void VertexArray::bind() {
            glBindVertexArray(m_VAO);
            CHECK_IF_GL_ERROR("Failed to bind m_VAO");
        }

        void VertexArray::unbind() {
            glBindVertexArray(0);
        }

        void VertexArray::setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
            glEnableVertexAttribArray(index);
            CHECK_IF_GL_ERROR("Failed to set attribute pointer");
        }
} // GL