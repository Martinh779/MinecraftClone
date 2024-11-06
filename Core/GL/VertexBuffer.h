//
// Created by Martin Hertel on 29.07.2024.
//

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
