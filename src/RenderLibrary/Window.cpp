#include "StdAfx.h"

#include "RenderDebugUtils.h"

#include <string>
#include <list>

#include "InputCodes.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Log.hpp"

using namespace ShaderPlayground;

//HWND Window::_ptrHwnd = nullptr;
Window* Window::_wndthis = nullptr;

Window::Window(void) :
    _inputmgr(nullptr),
    _hwnd(0),
    _isexit(false),
    _active(true),
    _minimized(false),
    _maximized(false),
    _isresize(false), 
    width(640),
    height(480),
    posx(200),
    posy(20), resizing(true) {
    if (!_wndthis) {
        _wndthis = this;
        //_ptrHwnd = HWND();
    } else {
        Log::Get()->Err("Window уже был создан");
    }
}

#ifdef ONLY_RENDER
bool Window::Create()
#else
window_handle Window::CreateHWND(window_handle parent)
#endif
{
    Log::Get()->Debug("Window Create");

    //_desc = this;

    WNDCLASSEXW wnd{};

    wnd.cbSize = sizeof(WNDCLASSEXW);
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc = StaticWndProc;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hInstance = 0;
    wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wnd.hIconSm = wnd.hIcon;
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wnd.lpszMenuName = NULL;
    wnd.lpszClassName = L"D3D11F";
    wnd.cbSize = sizeof(WNDCLASSEX);

#ifdef ONLY_RENDER
    if (!RegisterClassEx(&wnd)) {
        Log::Get()->Err("Не удалось зарегистрировать окно");
        return false;
    }

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);
#else
    RegisterClassEx(&wnd);
    RECT rect{};
    GetWindowRect(parent, &rect);

    AdjustWindowRect(&rect, WS_CHILD, FALSE);
#endif

    long lwidth = rect.right - rect.left;
    long lheight = rect.bottom - rect.top;

    long lleft = (long)posx;
    long ltop = (long)posy;

#ifdef ONLY_RENDER
    _hwnd = CreateWindowEx(NULL, 
        wnd.lpszClassName,
        L"DX11 Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        lleft, 
        ltop, 
        lwidth, 
        lheight, 
        NULL, 
        NULL, 
        NULL, 
        NULL);

    if (!_hwnd) {
        Log::Get()->Err("Не удалось создать окно");
        return false;
    }

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    return true;
#else
    _hwnd = CreateWindowEx(NULL, wnd.lpszClassName, L"DX11 Window", WS_CHILD, lleft, ltop, lwidth, lheight, parent, NULL, NULL, NULL);

    ShowWindow(_hwnd, SW_SHOWNORMAL);
    UpdateWindow(_hwnd);

    return _hwnd;
#endif
}



void Window::RunEvent() {
    MSG msg; // события окна
    // просматриваем все поступившие события
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::Close() {
    if (_hwnd /*&& _ptrHwnd*/) {
        DestroyWindow(_hwnd);
        //DestroyWindow(_ptrHwnd);
    }
    _hwnd = nullptr;
    /*delete *///_ptrHwnd = nullptr;
    //Log::Get()->Debug("Pointer to window handle: %p", std::to_string(reinterpret_cast<int>(_ptrHwnd)));
    Log::Get()->Debug("Window Close");
}

LRESULT Window::WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
    switch (nMsg) {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        _isexit = true;
        return 0;
    case WM_ACTIVATE:
        if (LOWORD(wParam) != WA_INACTIVE) {
            _active = true;
        } else {
            _active = false;
        }
        return 0;
    case WM_MOVE:
        /*_desc.*/posx = LOWORD(lParam);
        /*_desc.*/posy = HIWORD(lParam);
        UpdateWindowState();
        return 0;
    case WM_SIZE:
        if (!/*_desc.*/resizing) {
            return 0;
        }
        /*_desc.*/width = LOWORD(lParam);
        /*_desc.*/height = HIWORD(lParam);
        _isresize = true;
        if (wParam == SIZE_MINIMIZED) {
            _active = false;
            _minimized = true;
            _maximized = false;
        } else if (wParam == SIZE_MAXIMIZED) {
            _active = true;
            _minimized = false;
            _maximized = true;
        } else if (wParam == SIZE_RESTORED) {
            if (_minimized) {
                _active = true;
                _minimized = false;
            } else if (_maximized) {
                _active = true;
                _maximized = false;
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
        if (_inputmgr) {
            _inputmgr->Run(nMsg, wParam, lParam);
        }
        return 0;
    }

    return DefWindowProcW(hwnd, nMsg, wParam, lParam);
}

void Window::SetInputMgr(InputManager* inputmgr)
{
    _inputmgr = inputmgr;
    UpdateWindowState();
}

void Window::UpdateWindowState() {
    RECT clientRect{};
    clientRect.left = /*_desc.*/posx;
    clientRect.top = /*_desc.*/posy;
    clientRect.right = /*_desc.*/width;
    clientRect.bottom = /*_desc.*/height;
    if (_inputmgr) {
        _inputmgr->SetWinRect(clientRect);
    }
}

LRESULT CALLBACK ShaderPlayground::StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
    return Window::Get()->WndProc(hwnd, nMsg, wParam, lParam);
}
