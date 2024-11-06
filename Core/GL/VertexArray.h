//
// Created by Martin Hertel on 29.07.2024.
//

#ifndef MINECRAFTCLONE_VERTEXARRAY_H
#define MINECRAFTCLONE_VERTEXARRAY_H

#include "glad/glad.h"

namespace GL {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();

        void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

    private:
        GLuint m_VAO;
    };

} // GL

#endif //MINECRAFTCLONE_VERTEXARRAY_H
