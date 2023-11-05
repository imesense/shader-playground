#include "..\..\Headers\framework.h"
#include "..\..\Headers\Render.h"
#include "..\..\Headers\Main.h"
#include "..\..\Headers\DirectX11\DirectX11.h"

/*
    Сохраняет маркер экземпляра и создает главное окно

    В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
    создается и выводится главное окно программы.
*/
BOOL window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    pDirectX11 = new DirectX11();

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);

    pDirectX11->CreateWindowDirectX11(hWnd);

    UpdateWindow(hWnd);

    return TRUE;
}