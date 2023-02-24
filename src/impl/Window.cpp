#include "Window.h"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int w, int h){
    glViewport(0, 0, w, h);
}

Window::Window(int Width, int Height, const char* WindowTitle, int Majorver, int Minorver){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Majorver);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Minorver);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(Width, Height, WindowTitle, NULL, NULL);
    if (window == NULL){
        cout << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}


void Window::Terminate(){
    glfwTerminate();
}
