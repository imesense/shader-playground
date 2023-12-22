#include "StdAfx.h"

/* Disable rarely used windows stuff */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <list>
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

#include "RenderDebugUtils.h"

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "RenderState.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "DepthShader.hpp"
#include "RenderTarget.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "DX11ViewRender.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Log.hpp"
#include "Framework.hpp"
#include "Exports.h"
#include "Helpers.h"

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

using namespace ShaderPlayground;

#define DLL_EXPORT extern "C" __declspec(dllexport)
using window_handle = HWND;

window_handle window{ nullptr };

bool InitializeDirectX(HWND hwnd);
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
DLL_EXPORT window_handle InitializeWin32(window_handle parent)
{
    /* Create window class */
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = window_proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(156, 219, 101)); // Red Background color
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"DX11Window";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    /* Register window class */
    RegisterClassEx(&wc);
    RECT rect{};
    GetWindowRect(parent, &rect);

    /* Adjust window style to current devie size */
    AdjustWindowRect(&rect, WS_CHILD, FALSE);

    const int top{ rect.top };
    const int left{ rect.left };
    const int init_width{ rect.right - left };
    const int init_height{ rect.bottom - top };

    const wchar_t* caption{ L"DX11 Window caption" };

    /* Create an instance of the window class */
    window = CreateWindowEx(
        0,						// extended style
        wc.lpszClassName,		// window class name
        caption,				// instance title
        WS_CHILD,				// window style
        left,					// initial window left position
        top,					// initial window top position
        init_width,				// initial window width
        init_height,			// initial window height
        parent,					// handle to parent window
        NULL,					// handle to menu
        NULL,					// instance of this application
        NULL					// extra creation parameters
    );

    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);

    if (!InitializeDirectX(window))
    {
        // Обработка ошибки и выход
        return nullptr;
    }

    return window;
}

bool InitializeDirectX(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC sc_desc = {};
    sc_desc.BufferCount = 2;
    sc_desc.BufferDesc.Width = 0;
    sc_desc.BufferDesc.Height = 0;
    sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sc_desc.BufferDesc.RefreshRate.Numerator = 60;
    sc_desc.BufferDesc.RefreshRate.Denominator = 1;
    sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc_desc.OutputWindow = hwnd;
    sc_desc.SampleDesc.Count = 1;
    sc_desc.SampleDesc.Quality = 0;
    sc_desc.Windowed = TRUE;

    // Create the device, device context, and swap chain
    if (D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sc_desc,
        &g_pSwapChain,
        &g_pd3dDevice,
        nullptr,
        &g_pd3dDeviceContext) != S_OK)
    {
        // Обработка ошибки и выход
        return false;
    }

    return true;
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        break;
    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}
