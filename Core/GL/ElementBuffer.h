/*
 * Copyright (c) 2024 Martin Hertel.
 *
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 */

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
