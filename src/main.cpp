#include "glad/glad.h"
#include "inc/Shader.h"
#include "inc/Texture.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "inc/VAO.h"
#include "inc/VBO.h"
#include "inc/EBO.h"
#include "inc/Window.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "inc/glm/gtc/matrix_transform.hpp"
#define Width 800
#define Height 600

using namespace std;


float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};   

unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};


float showVal = 0.0f;

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if (showVal <= 1.0f) {
            showVal = showVal + 0.1f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if (showVal >= 0.0f){
            showVal = showVal - 0.1f;
        }
    }
}

int main(){
    Window mainWindow(Width, Height, "Window", 3, 3);
    Shader* vertShader = new Shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    
    // ==========================
    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    VBO vbo2(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    
    vao.LinkVbo(&vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkVbo(&vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    vao.LinkVbo(&vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));

    vao.LinkVbo(&vbo2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkVbo(&vbo2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    vao.LinkVbo(&vbo2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));

    Texture texture1("assets/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture texture2("assets/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    texture1.TexUnit(vertShader, "tex1", 0);
    texture2.TexUnit(vertShader, "tex2", 1);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    while(!glfwWindowShouldClose(mainWindow.window)){
        processInput(mainWindow.window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture1.Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();
        vertShader->use();
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        vertShader->setMat4("trans", trans);
        vertShader->setFloat("ratio", showVal);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        vertShader->setMat4("trans", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(mainWindow.window);
        glfwPollEvents();
    }
    vbo.Delete();
    ebo.Delete();
    vao.Delete();
    texture2.Delete();
    texture1.Delete();
    mainWindow.Terminate();
    delete vertShader;
    return 0;
}
