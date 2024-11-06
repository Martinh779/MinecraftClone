//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_ELEMENTBUFFER_H
#define MINECRAFTCLONE_ELEMENTBUFFER_H

#include "glad/glad.h"

namespace GL {

    class ElementBuffer {
    public:
        ElementBuffer();
        ~ElementBuffer();

        void bind();
        void unbind();
        void bufferData(GLsizeiptr size, void* data, GLenum usage);

    private:
        GLuint m_EBO;
    };

} // GL

#endif //MINECRAFTCLONE_ELEMENTBUFFER_H
