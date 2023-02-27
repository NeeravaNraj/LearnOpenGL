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
#include "inc/glm/detail/type_vec.hpp"
#include "inc/glm/gtc/matrix_transform.hpp"
#include "inc/Camera.h"
#define Width 800
#define Height 600

using namespace std;


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 cubePos[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  0.0f, 2.0f), 
};

glm::vec3 cubeScale[] = {
    glm::vec3( 1.0f,  1.0f,  1.0f), 
    glm::vec3(0.4f, 0.4f, 0.4f) 
};
unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = Width / 2.0f, lastY = Height / 2.0f; 
float showVal = 1.0f;

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        showVal = showVal + 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        showVal = showVal - 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Right, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(Up, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(Down, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset){
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

int main(){
    Window mainWindow(Width, Height, "Window", 3, 3);
    glfwSetInputMode(mainWindow.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mainWindow.window, mouse_callback);
    glfwSetScrollCallback(mainWindow.window, scroll_callback);
    Shader* vertShader = new Shader("src/shader/vertex.vert", "src/shader/fragment.frag");
    Shader lightCube("src/shader/lighting.vert", "src/shader/lighting.frag");
    // ==========================
    VAO vao, lightVao;

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    
    vao.Bind();
    vao.LinkVbo(&vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkVbo(&vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3* sizeof(float)));
    lightVao.Bind();
    lightVao.LinkVbo(&vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    lightVao.Unbind();

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(mainWindow.window)){
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(mainWindow.window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vertShader->use();
        vertShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        vertShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Width / (float)Height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos[0]);
        model = glm::scale(model, cubeScale[0]);

        vertShader->setMat4("projection", projection);
        vertShader->setMat4("view", view);
        vertShader->setMat4("model", model);
        vertShader->setVec3("lightPos", cubePos[1]);
        vertShader->setVec3("viewPos", camera.Position);

        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        model = glm::mat4(1.0f);
        cubePos[1].x = sin(glfwGetTime()) * 2.0f;
        cubePos[1].z = cos(glfwGetTime()) * 2.0f;
        cubePos[1].y = sin(glfwGetTime());
        model = glm::translate(model, cubePos[1]);
        model = glm::scale(model, cubeScale[1]);

        lightCube.use();
        lightCube.setMat4("projection", projection);
        lightCube.setMat4("view", view);
        lightCube.setMat4("model", model);

        lightVao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(mainWindow.window);
        glfwPollEvents();
    }
    vbo.Delete();
    ebo.Delete();
    vao.Delete();
    lightVao.Delete();
    mainWindow.Terminate();
    delete vertShader;
    return 0;
}
