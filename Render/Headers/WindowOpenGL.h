#pragma once
#include "Headers/framework.h"

extern GLenum g_OpenGLError;

#define LOG_ERROR(str,...)

#define OPENGL_CALL(expression) \
	{ \
		expression; \
		if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
			LOG_ERROR("OpenGL expression \"" #expression "\" error %d\n", (int)g_OpenGLError); \
	}

#define OPENGL_CHECK_FOR_ERRORS() \
	if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
		LOG_ERROR("OpenGL error %d\n", (int)g_OpenGLError);

namespace WindowOpenGL
{
	class WindowOpenGL
	{
	public:
		struct GLWindow
		{
			//-' Размеры окна
			int width;
			int height;

			//-' Флаги состояние
			bool active;
			bool running;
		};

		bool GLWindowCreate(const char* title, int width, int height);
		void GLWindowDestroy();

		void GLWindowSetSize(int width, int height);

		int GLWindowMainLoop();

		static LRESULT CALLBACK GLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

extern WindowOpenGL::WindowOpenGL* pWindowOpenGL;