#include "..\..\Headers\framework.h"
#include "..\..\Headers\Render.h"
#include "..\..\Headers\Main.h"

/*
    Обработчик сообщений для окна "О программе"
*/

INT_PTR CALLBACK window::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    //UNREFERENCED_PARAMETER(lParam);
    //switch (message)
    //{
    //case WM_INITDIALOG:
    //    return (INT_PTR)TRUE;

    //case WM_COMMAND:
    //    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    //    {
    //        EndDialog(hDlg, LOWORD(wParam));
    //        return (INT_PTR)TRUE;
    //    }
    //    break;
    //}
    return 0;//(INT_PTR)FALSE;
}
