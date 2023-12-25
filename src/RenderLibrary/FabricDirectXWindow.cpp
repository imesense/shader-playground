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
#include "Exports.h"
#include "Helpers.h"

#include "FabricDirectXWindow.h"

using namespace ShaderPlayground;

struct FabricDirectXWindow
{
    HWND window = nullptr;

    DX11ViewRender* render = nullptr;
    InputBinder* inputBinder = nullptr;

} fabric_directx_window;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

RENDERLIBRARY_API HWND CreateFabricDirectXWindow() {
    const wchar_t CLASS_NAME[] = L"DirectX11";

    fabric_directx_window.render = new DX11ViewRender();
    fabric_directx_window.inputBinder = new InputBinder(fabric_directx_window.render);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = 0;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 156, 65));
    wc.lpszClassName = CLASS_NAME;

    RegisterClassExW(&wc);

    // Create the window.

    fabric_directx_window.window = CreateWindowW(
        CLASS_NAME, // Window class
        L"DirectX11 Window",     // Window text

        // Window style
        WS_POPUP | WS_VISIBLE | WS_SYSMENU,

        // Size and position
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,

        nullptr, // Parent window
        nullptr, // Menu
        nullptr, // Instance handle
        nullptr  // Additional application data
    );

    if (!fabric_directx_window.render->CreateDevice(fabric_directx_window.window)) {
       // Log::Get()->Err("Не удалось создать рендер");
        return NULL;
    }
    //else
    //{
    //   // Log::Get()->Err("DirectX11 создан");
    //}

    ShowWindow(fabric_directx_window.window, SW_SHOWNORMAL);
    //if (!fabric_directx_window.render->CreateDevice(fabric_directx_window.window))
    //{
    //    return NULL;
   // }
    UpdateWindow(fabric_directx_window.window);

    return fabric_directx_window.window;
}

RENDERLIBRARY_API void DestroyFabricDirectXWindow()
{
    delete fabric_directx_window.window;
}
