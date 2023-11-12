#include "stdafx.h"
#include "OpenGLWndProc.h"
#include "../OpenGL/CreateWindowGL.h"

namespace OpenGLProc
{
	LRESULT CALLBACK GLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				g_window.running = false;

			//if (wParam == VK_F1)
			//	GLWindowSetSize(g_window.width, g_window.height/*, !g_window.fullScreen*/);

			return FALSE;

		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			g_window.active = (msg == WM_SETFOCUS);
			return FALSE;

		case WM_ACTIVATE:
			g_window.active = (LOWORD(wParam) == WA_INACTIVE);
			return FALSE;

		case WM_CLOSE:
			g_window.running = g_window.active = false;
			PostQuitMessage(0);
			return FALSE;

		case WM_SYSCOMMAND:
			switch (wParam & 0xFFF0)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				/*if (g_window.fullScreen)
					return FALSE;*/
				break;

			case SC_KEYMENU:
				return FALSE;
			}
			break;

		case WM_ERASEBKGND:
			return FALSE;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}