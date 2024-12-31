/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#include "VertexBuffer.h"

namespace GL {

        VertexBuffer::VertexBuffer() {
            glGenBuffers(1, &m_VBO);
        }

        VertexBuffer::~VertexBuffer() {
            glDeleteBuffers(1, &m_VBO);
        }

        void VertexBuffer::bind() {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        }

        void VertexBuffer::unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void VertexBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage) {
            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        }
} // GL