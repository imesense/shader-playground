#include "stdafx.h"
#include "DirectXWndProc.h"
#include "../DirectX/CreateWindowDX.h"

using namespace WindowDirectX;

namespace DirectXProc
{
	LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (nMsg)
		{
		case WM_CREATE:
			return 0;
		case WM_CLOSE:
			m_pGetWndDX->SetIsExit(true);
			return 0;
		case WM_ACTIVATE:
			if (LOWORD(wParam) != WA_INACTIVE)
				m_pGetWndDX->SetActive(true);
			else
				m_pGetWndDX->SetActive(false);
			return 0;
		case WM_MOVE:
			m_pGetWndDX->UpdatePosition(LOWORD(lParam), HIWORD(lParam));
			m_pGetWndDX->m_UpdateWindowState();

			return 0;
		case WM_SIZE:
			if (m_pGetWndDX->CheckNotRsizing())
				return 0;

			m_pGetWndDX->UpdateSizeWindow(LOWORD(lParam), HIWORD(lParam));

			m_pGetWndDX->SetResize(true);

			if (wParam == SIZE_MINIMIZED)
			{
				m_pGetWndDX->SetActive(false);
				m_pGetWndDX->SetMinimized(true);
				m_pGetWndDX->SetMaximized(false);
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				m_pGetWndDX->SetActive(true);
				m_pGetWndDX->SetMinimized(false);
				m_pGetWndDX->SetMaximized(true);
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (m_pGetWndDX->GetMinimized())
				{
					m_pGetWndDX->SetActive(true);
					m_pGetWndDX->SetMinimized(false);
				}
				else if (m_pGetWndDX->GetMaximized())
				{
					m_pGetWndDX->SetActive(true);
					m_pGetWndDX->SetMaximized(false);
				}
			}

			m_pGetWndDX->m_UpdateWindowState();

			return 0;
		case WM_MOUSEMOVE: case WM_LBUTTONUP: case WM_LBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDOWN: case WM_MOUSEWHEEL: case WM_KEYDOWN: case WM_KEYUP:

			if (m_pGetWndDX->Input())
				m_pGetWndDX->Input()->Run(nMsg, wParam, lParam);

			return 0;
		}

		return DefWindowProcW(hwnd, nMsg, wParam, lParam);
	}
}