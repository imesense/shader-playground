#pragma once

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
	struct GLWindow
	{
		//-' Размеры окна
		int width;
		int height;

		//-' Флаги состояние
		bool active;
		bool running;
	};

	class WindowOpenGL
	{
	public:
		HDC g_hDC;
		HGLRC g_hRC;
		HWND g_hWnd;

		HINSTANCE g_hInstance;

		RECT rect;
		HGLRC hRCTemp;
		DWORD style, exStyle;

		WNDCLASSEX wcx;
		PIXELFORMATDESCRIPTOR pfd;

		int x, y, format;

		bool GLWindowCreate(const char* title, int width, int height);
		void GLWindowDestroy();

		void GLWindowSetSize(int width, int height);

		int GLWindowMainLoop();
	};
}

extern GLenum g_OpenGLError;
extern WindowOpenGL::GLWindow g_window;
extern WindowOpenGL::WindowOpenGL* pWindowOpenGL;