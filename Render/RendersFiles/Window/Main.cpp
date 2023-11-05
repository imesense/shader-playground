#pragma once
#include "..\..\Headers\framework.h"

namespace window
{
	//-' Глобальные переменные:
	HINSTANCE hInst; //-' текущий экземпляр

	WCHAR szTitle[100]; //-' Текст строки заголовка
	WCHAR szWindowClass[100]; //-' имя класса главного окна

	//-' Отправить объявления функций, включенных в этот модуль кода:	
	BOOL InitInstance(HINSTANCE, int);
	ATOM _RegisterClass(HINSTANCE hInstance);

	INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}