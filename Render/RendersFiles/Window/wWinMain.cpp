#include "stdafx.h"

#include "Headers\framework.h"
#include "Headers\Main.h"

#include "Headers\WindowOpenGL.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	int result;
#if 0
	// Создаем объект Window
	window::Window wnd;

	result = 1;

	// Заполняем DescWindow структуру с нужными параметрами
	window::DescWindow desc;
	desc.width = 1280;
	desc.height = 720;
	desc.caption = L"DirectX Window";

	// Вызываем метод Create
	bool success = wnd.Create(desc);

	if (success)
	{
		// Окно успешно создано, можно начинать обработку сообщений
		while (!wnd.IsExit())
		{
			wnd.RunEvent();
			// Здесь можно добавить свой код для обработки событий
		}
	}
#else
	//LoggerCreate("lesson01.log");

	pWindowOpenGL = new WindowOpenGL::WindowOpenGL();

	if (!pWindowOpenGL->GLWindowCreate("OpenGL Window", 1280, 720/*, false*/))
		return 1;

	result = pWindowOpenGL->GLWindowMainLoop();

	pWindowOpenGL->GLWindowDestroy();
	delete pWindowOpenGL;
	//LoggerDestroy();
#endif

	return result;
}