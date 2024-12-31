/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

#ifndef MINECRAFTCLONE_VERTEXBUFFER_H
#define MINECRAFTCLONE_VERTEXBUFFER_H

#include "glad/glad.h"

namespace GL {

    class VertexBuffer {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void bind();
        void unbind();

        void bufferData(GLsizeiptr size, void* data, GLenum usage);

    private:
        GLuint m_VBO;
    };

} // GL

#endif //MINECRAFTCLONE_VERTEXBUFFER_H
