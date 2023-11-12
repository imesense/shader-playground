#include "stdafx.h"
#include "CreateWindowDX.h"
#include "../DirectX/DirectXWndProc.h"
#include "../DirectX/dx10DeviceHW.h"
#include "../DirectX/dx11DeviceHW.h"

using namespace dx10HW;
using namespace dx11HW;
using namespace DirectXProc;

WindowDirectX::CWindowDirectX* m_pGetWndDX = nullptr;

namespace WindowDirectX
{
	CWindowDirectX::CWindowDirectX()
	{
		m_hWnd = {};
		WndCls = {};
		m_pInput = {};
		m_isexit = {};
		m_active = {};
		m_minimized = {};
		m_maximized = {};
		m_isresize = {};
	}

	CWindowDirectX::~CWindowDirectX()
	{
	
	}

	bool CWindowDirectX::Create(const Description& desc, bool dx11)
	{
		WndDescr = desc;

		WndCls.cbSize = sizeof(WNDCLASSEXW);
		WndCls.style = CS_HREDRAW | CS_VREDRAW;
		WndCls.lpfnWndProc = StaticWndProc;
		WndCls.cbClsExtra = 0;
		WndCls.cbWndExtra = 0;
		WndCls.hInstance = 0;
		WndCls.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		WndCls.hIconSm = WndCls.hIcon;
		WndCls.hCursor = LoadCursor(0, IDC_ARROW);
		WndCls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		WndCls.lpszMenuName = NULL;
		WndCls.lpszClassName = L"D3D";
		WndCls.cbSize = sizeof(WNDCLASSEX);

		if (!RegisterClassEx(&WndCls))
			return false;

		RECT rect = { 0, 0, WndDescr.width, WndDescr.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

		long lwidth = rect.right - rect.left;
		long lheight = rect.bottom - rect.top;

		long lleft = (long)WndDescr.posx;
		long ltop = (long)WndDescr.posy;

		m_hWnd = CreateWindowEx(NULL, L"D3D", WndDescr.caption.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, lleft, ltop, lwidth, lheight, NULL, NULL, NULL, NULL);

		if (!m_hWnd)
			return false;

		ShowWindow(m_hWnd, SW_SHOW);

		if (dx11)
		{
			pDirectX11 = new DirectX11();
			pDirectX11->CreateWindowDirectX11(m_hWnd);
		}
		else
		{
			pDirectX10 = new DirectX10();
			pDirectX10->CreateWindowDirectX10(m_hWnd);
		}

		UpdateWindow(m_hWnd);

		return true;
	}

	void CWindowDirectX::RunEvent()
	{
		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void CWindowDirectX::Close()
	{
		if (m_hWnd)
			DestroyWindow(m_hWnd);

		m_hWnd = nullptr;

		if (!pDirectX10)
		{
			delete pDirectX10;
		}

		if (!pDirectX11)
		{
			delete pDirectX11;
		}
	}

	void CWindowDirectX::m_UpdateWindowState()
	{
		RECT ClientRect;
		ClientRect.left = WndDescr.posx;
		ClientRect.top = WndDescr.posy;
		ClientRect.right = WndDescr.width;
		ClientRect.bottom = WndDescr.height;

		if (m_pInput)
			m_pInput->SetWinRect(ClientRect);
	}

	void CWindowDirectX::SetInput(CInput* Input)
	{
		m_pInput = Input;
		m_UpdateWindowState();
	}
}