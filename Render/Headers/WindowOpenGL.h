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
	// структура для хранения стейта окна GLWindow
	struct GLWindow
	{
		// размеры окна
		int width;
		int height;

		// флаги состояние
		bool fullScreen;
		bool active;
		bool running;
	};

	bool GLWindowCreate(const char* title, int width, int height, bool fullScreen = false);
	void GLWindowDestroy();

	void GLWindowSetSize(int width, int height, bool fullScreen = false);

	int GLWindowMainLoop();
}