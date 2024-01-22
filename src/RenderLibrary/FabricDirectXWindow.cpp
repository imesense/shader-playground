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
#include <map>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "RenderState.hpp"
#include <wrl/client.h>
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
#include "Exports.hpp"
#include "Helpers.hpp"
#include "../MultiLogManager/Exports.hpp"
#include "../MultiLogManager/Log/Log.hpp"
#include "FabricDirectXWindow.hpp"
#include "BitmapFont.hpp"
#include "RenderText.hpp"

using namespace ShaderPlayground;

struct FabricDirectXWindow
{
    MSG msg;
    HWND window;
    RECT clientRect;

    int posx;
    int posy;

    int width;
    int height;

    bool resizing;

    bool _isexit;
    bool _active;
    bool _minimized;
    bool _maximized;
    bool _isresize;

    DX11ViewRender* render;
    InputBinder* inputBinder;

} fabric_directx_window;

void UpdateWindowState() {
    fabric_directx_window.clientRect.left = fabric_directx_window.posx;
    fabric_directx_window.clientRect.top = fabric_directx_window.posy;
    fabric_directx_window.clientRect.right = fabric_directx_window.width;
    fabric_directx_window.clientRect.bottom = fabric_directx_window.height;
    //if (_inputmgr) {
    //    _inputmgr->SetWinRect(clientRect);
    //}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        return 0;
    case WM_ACTIVATE:
        return 0;
    case WM_MOVE:
        return 0;
    case WM_SIZE:
        return 0;
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
    case WM_LBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_MOUSEWHEEL:
    case WM_KEYDOWN:
    case WM_KEYUP:
        //Log::Get()->Print("WM_KEYUP");
        /*if (_inputmgr) {
            _inputmgr->Run(msg, wParam, lParam);
        }*/
        pLog->Write("Update: ", "%s", __FUNCTION__);
        return 0;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}

RENDERLIBRARY_API HWND CreateFabricDirectXWindow() {
    const wchar_t CLASS_NAME[] = L"DirectX11";

    pLog = new CLog();
    pLog->CreateFileSettings();
    pLog->CreateLog();

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

    fabric_directx_window.window = CreateWindowW(
        CLASS_NAME,
        L"DirectX11 Window",
        WS_POPUP | WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
        nullptr, nullptr, nullptr, nullptr
    );
   
    pLog->Write("Window HWND pointer: ", "%p", fabric_directx_window.window);

    ShowWindow(fabric_directx_window.window, SW_SHOWNORMAL);
    UpdateWindow(fabric_directx_window.window);

    return fabric_directx_window.window;
}

RENDERLIBRARY_API void CreateScene(HWND ptr) {
    fabric_directx_window.render->CreateDevice(ptr);
}

RENDERLIBRARY_API void MessageLoop() {
    while (PeekMessage(&fabric_directx_window.msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&fabric_directx_window.msg);
        DispatchMessage(&fabric_directx_window.msg);
    }
}

RENDERLIBRARY_API void DestroyFabricDirectXWindow() {
    delete pLog;
    delete fabric_directx_window.window;
}

RENDERLIBRARY_API bool Frame() {
    MessageLoop();

    fabric_directx_window.render->BeginFrame();

    if (!fabric_directx_window.render->Draw()) {
        return false;
    }

    fabric_directx_window.render->EndFrame();

    return true;
}

