#pragma once

namespace OpenGLProc
{
	LRESULT CALLBACK GLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		return GLWindowProc(hwnd, nMsg, wParam, lParam);
	}
}