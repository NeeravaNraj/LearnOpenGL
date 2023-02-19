#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include "iostream"
#include "Shader.h"

class Texture {
   public:
       GLuint ID;
       GLenum type;
       Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

       void TexUnit(Shader* shader, const char* uniform, GLuint unit);
       void Bind();
       void Unbind();
       void Delete();
};
#endif
