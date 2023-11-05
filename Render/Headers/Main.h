#pragma once
#include "..\Headers\framework.h"

namespace window
{
	//-' Глобальные переменные:
	extern HINSTANCE hInst; //-' текущий экземпляр

	extern WCHAR szTitle[100]; //-' Текст строки заголовка
	extern WCHAR szWindowClass[100]; //-' имя класса главного окна

	//-' Отправить объявления функций, включенных в этот модуль кода:	
	extern BOOL InitInstance(HINSTANCE, int);
	extern ATOM _RegisterClass(HINSTANCE hInstance);

	extern INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
	extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}