#include "..\..\Headers\framework.h"
#include "..\..\Headers\Render.h"
#include "..\..\Headers\Main.h"
#include "..\..\Headers\DirectX10\DirectX10.h"
#include "..\..\Headers\DirectX11\DirectX11.h"

/*
    Обрабатывает сообщения в главном окне

    WM_COMMAND  - обработать меню приложения
    WM_PAINT    - Отрисовка главного окна
    WM_DESTROY  - отправить сообщение о выходе и вернуться
*/
LRESULT CALLBACK window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            //    break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        //g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, Colors::CornflowerBlue);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);

        if (pDirectX10 != nullptr)
            pDirectX10->g_pSwapChain->Present(TRUE, 0);

        if (pDirectX11 != nullptr)
            pDirectX11->g_pSwapChain->Present(TRUE, 0);
    }
    break;
    case WM_DESTROY:
        if (pDirectX10 != nullptr)
            delete pDirectX10;

        if (pDirectX11 != nullptr)
            delete pDirectX11;

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}