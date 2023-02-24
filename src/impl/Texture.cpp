#include "Texture.h"
#include "../inc/stb.h"
/* #include <GL/gl.h> */

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, bool flipImage){
    int width, height, nrChannels;
    type = texType;

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_set_flip_vertically_on_load_thread(flipImage);
    unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
        glGenerateMipmap(texType);
    } else {
        cout << "Failed to load Texture!\n";
    }
   stbi_image_free(data); 
   this->Unbind();
}


void Texture::TexUnit(Shader *shader, const char* uniform, GLuint unit){
    /* this->Bind(); */
    shader->use();
    shader->setInt(uniform, unit);
}

void Texture::Bind(){
    glBindTexture(type, ID);
}

void Texture::Unbind(){
    glBindTexture(type, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}
