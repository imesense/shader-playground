#include "stdafx.h"
#include "Headers\framework.h"
#include "Headers\Render.h"
#include "Headers\Main.h"
#include "Headers\DirectX10\DirectX10.h"
#include "Headers\DirectX11\DirectX11.h"
#include "Headers\OpenGL\OpenGL.h"

/*
    Сохраняет маркер экземпляра и создает главное окно

    В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
    создается и выводится главное окно программы.
*/
BOOL window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
#ifndef OPEN_GL
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    pDirectX10 = new DirectX10();

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);

    pDirectX10->CreateWindowDirectX10(hWnd);

    UpdateWindow(hWnd);
#else
    pOpenGL = new OpenGL();

    pOpenGL->CreateWindowOpenGL();
#endif

    return TRUE;
}