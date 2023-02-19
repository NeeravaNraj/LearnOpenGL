#ifndef INIT_H
#define INIT_H
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
class Window {
    public:
        GLFWwindow *window;
        Window(int Width, int Height, const char* WindowTitle, int Majorver, int Minorver);
        void Terminate();
};

#endif // !DEBUG
