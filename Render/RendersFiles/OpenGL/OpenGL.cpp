#include "stdafx.h"
#include "Headers\OpenGL\OpenGL.h"

OpenGL* pOpenGL = nullptr;

OpenGL::OpenGL()
{

}

OpenGL::~OpenGL()
{

}

BOOL OpenGL::CreateWindowOpenGL()
{
    // Initialize GLFW
    if (!glfwInit())
        return FALSE;

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return FALSE;
    }

    // Set the GLFW window as the current context
    glfwMakeContextCurrent(window);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void OpenGL::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

//-' Callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}