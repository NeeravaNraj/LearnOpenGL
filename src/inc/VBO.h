#ifndef VBO_H
#define VBO_H
#include "glad/glad.h"
#include "iostream"

class VBO {
    public:
        uint ID;
        VBO(GLfloat* verts, GLsizeiptr size);
        void Bind(void);
        void Unbind(void);
        void Delete(void);
};

#endif
