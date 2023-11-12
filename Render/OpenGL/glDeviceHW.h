#pragma once

#include <GLFW/glfw3.h>

namespace glHW
{
    class OpenGLWindowsObjects
    {
    public:
        OpenGLWindowsObjects();
        ~OpenGLWindowsObjects();
    };
}

extern glHW::OpenGLWindowsObjects* pOpenGL;