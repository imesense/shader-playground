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

using namespace ShaderPlayground;

#if 0
LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

using window_handle = HWND;
window_handle window = nullptr;

typedef struct
{
    int posx;
    int posy;

    int width; // ширина клиентской части окна
    int height; // высота клиентской части окна
    bool resizing;

    bool _isexit; // флаг сообщающий о событии выхода
    bool _active; // окно активно?
    bool _minimized;
    bool _maximized;
    bool _isresize; // если окно изменило размер

    Render* _render;
    InputManager* _input;

    RECT clientRect;
    MSG msg;
} WindowControl;

WindowControl objControl;

DX11ViewRender* render = new DX11ViewRender();
InputBinder* input = new InputBinder(render);

extern "C" __declspec(dllexport)
window_handle InitializeWin32(window_handle parent)
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

    objControl._render = render;

    Log::Get()->Print(" %s - %p", __FUNCTION__, objControl._render);

    if (!objControl._render->CreateDevice(window)) {
        Log::Get()->Err("Не удалось создать рендер");
        return NULL;
    }
    else
    {
        Log::Get()->Err("DirectX11 создан");
    }

    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);

    return window;
}


void UpdateWindowState() {
    objControl.clientRect.left = objControl.posx;
    objControl.clientRect.top = objControl.posy;
    objControl.clientRect.right = objControl.width;
    objControl.clientRect.bottom = objControl.height;
    //if (_inputmgr) {
    //    _inputmgr->SetWinRect(clientRect);
    //}
}

void RunEvent() {
    while (PeekMessage(&objControl.msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&objControl.msg);
        DispatchMessage(&objControl.msg);
        Log::Get()->Print("Active3");
    }
    Log::Get()->Print("Active5");
}

extern "C" __declspec(dllexport)
bool Frame()
{
    // обрабатываем события окна
    //_wnd->RunEvent();
    RunEvent();
    Log::Get()->Print("- %i", __LINE__);
    // если окно неактивно - завершаем кадр
    /*if (!objControl._active) {
        return true;
    }*/
    Log::Get()->Print("- %i", __LINE__);
    // если окно было закрыто, завершаем работу движка
    if (objControl._isexit) {
        return false;
    }
    Log::Get()->Print("- %i", __LINE__);
    // если окно изменило размер
    if (objControl.resizing) {
    }
    Log::Get()->Print("- %i", __LINE__);
    objControl._render->BeginFrame();
    if (!objControl._render->Draw()) {
        return false;
    }
    objControl._render->EndFrame();
    Log::Get()->Print("Active0");
    Log::Get()->Print("- %i", __LINE__);
    return true;
}

extern "C" __declspec(dllexport)
void Run() {
    //if (_init) {
        while (Frame());
        Log::Get()->Print("Active1");
    //}
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //switch (msg)
    //{
    //case WM_CLOSE:
    //    DestroyWindow(hwnd);
    //    return 0;
    //case WM_DESTROY:
    //    PostQuitMessage(0);
    //    return 0;
    //case WM_SIZE:
    //    break;
    //default:
    //    break;
    //}

    //return DefWindowProc(hwnd, msg, wparam, lparam);
    switch (msg) {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        objControl._isexit = true;
        return 0;
    case WM_ACTIVATE:
        /*if (LOWORD(wparam) != WA_INACTIVE) {
            objControl._active = true;
        }
        else {
            objControl._active = false;
        }*/
        return 0;
    case WM_MOVE:
        objControl.posx = LOWORD(lparam);
        objControl.posy = HIWORD(lparam);
        UpdateWindowState();
        return 0;
    case WM_SIZE:
        if (!objControl.resizing) {
            return 0;
        }
        objControl.width = LOWORD(lparam);
        objControl.height = HIWORD(lparam);
        objControl._isresize = true;
        if (wparam == SIZE_MINIMIZED) {
            objControl._active = false;
            objControl._minimized = true;
            objControl._maximized = false;
        }
        else if (wparam == SIZE_MAXIMIZED) {
            objControl._active = true;
            objControl._minimized = false;
            objControl._maximized = true;
        }
        else if (wparam == SIZE_RESTORED) {
            if (objControl._minimized) {
                objControl._active = true;
                objControl._minimized = false;
            }
            else if (objControl._maximized) {
                objControl._active = true;
                objControl._maximized = false;
            }
        }
        UpdateWindowState();
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
        Log::Get()->Print("WM_KEYUP");
        /*if (_inputmgr) {
            _inputmgr->Run(msg, wParam, lParam);
        }*/
        return 0;
    }

    //Log::Get()->Print("ehehehehe");

    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

#endif

using window_handle = HWND;

struct RenderWindow
{
    window_handle window = nullptr;

    int posx;
    int posy;

    int width; // ширина клиентской части окна
    int height; // высота клиентской части окна
    bool resizing;

    bool _isexit; // флаг сообщающий о событии выхода
    bool _active; // окно активно?
    bool _minimized;
    bool _maximized;
    bool _isresize; // если окно изменило размер

    Render* _render;
    //InputManager* _input;

    RECT clientRect;
    MSG msg;
};

Render* pRender = nullptr;
DX11ViewRender* pViewRender = nullptr;
RenderWindow* pRenderWindow = nullptr;
InputManager* pInputManager = nullptr;
InputBinder* pInputBinder = nullptr;

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

RENDERLIBRARY_API window_handle CreateNativeWindow() {
    const wchar_t CLASS_NAME[] = L"WND";

    const auto CreatePointer = [&]() -> void
    {
        //pRender = new Render();
        pViewRender = new DX11ViewRender();
        pRenderWindow = new RenderWindow();
        pInputManager = new InputManager();
        pInputBinder = new InputBinder(pViewRender);
    };

    CreatePointer();

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

    pRenderWindow->window = CreateWindowW(
        CLASS_NAME, // Window class
        L"NativeWindow",     // Window text

        // Window style
        WS_POPUP | WS_VISIBLE | WS_SYSMENU,

        // Size and position
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,

        nullptr, // Parent window
        nullptr, // Menu
        nullptr, // Instance handle
        nullptr  // Additional application data
    );

    ShowWindow(pRenderWindow->window, SW_SHOWNORMAL);
    UpdateWindow(pRenderWindow->window);

    return pRenderWindow->window;
}

RENDERLIBRARY_API void DestroyNativeWindow()
{
    delete pViewRender;
    delete pRenderWindow;
    delete pInputManager;
    delete pInputBinder;
}
