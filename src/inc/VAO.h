#ifndef VAO_H
#define VAO_H
#include "glad/glad.h"
#include "iostream"
#include "VBO.h"

class VAO {
    public:
        uint ID;
        VAO();
        void LinkVbo(VBO* vbo, GLuint layout, GLuint componentCount, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();
};

#endif
