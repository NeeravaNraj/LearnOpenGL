#ifndef EBO_H
#define EBO_H
#include "glad/glad.h"
#include "iostream"

class EBO {
    public:
        uint ID;
        EBO(uint* indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};
#endif

