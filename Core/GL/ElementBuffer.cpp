//
// Created by Martin Hertel on 29.07.2024.
//

#include "ElementBuffer.h"

namespace GL {

        ElementBuffer::ElementBuffer() {
            glGenBuffers(1, &m_EBO);
        }

        ElementBuffer::~ElementBuffer() {
            glDeleteBuffers(1, &m_EBO);
        }

        void ElementBuffer::bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        }

        void ElementBuffer::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void ElementBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
        }
} // GL