#pragma once

namespace DirectXProc
{
	LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		return WndProc(hwnd, nMsg, wParam, lParam);
	}
}