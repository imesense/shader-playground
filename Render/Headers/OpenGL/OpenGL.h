#pragma once
#include "..\..\Headers\Render.h"

//#define OPEN_GL

#include <GLFW/glfw3.h>

class OpenGL
{
public:
    OpenGL();
    ~OpenGL();
    
    BOOL CreateWindowOpenGL();
public:
   
    void render();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    };
};

extern OpenGL* pOpenGL;
