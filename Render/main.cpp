#include "stdafx.h"
#include "../Constants/Constants.h"
#include "../DebugUtils/ManagerKeys.h"
#include "../DirectX/CreateWindowDX.h"

using namespace Constants;
using namespace ManagerKeys;
using namespace WindowDirectX;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	int result = -1;

	pIntConstantsArray = new IntConstantsArray();
	pCommandLineArguments = new CommandLineArguments();

	for (std::string& key : keys)
	{
		if (key == "-use_dx10" && pCommandLineArguments->CheckKey(key))
		{
			pIntConstantsArray->USE_DX10 = true;
			result = 0;
		}

		if (key == "-use_dx11" && pCommandLineArguments->CheckKey(key))
		{
			pIntConstantsArray->USE_DX11 = true;
			result = 1;
		}

		if (key == "-use_open_gl" && pCommandLineArguments->CheckKey(key))
		{
			pIntConstantsArray->USE_OPEN_GL = true;
			result = 2;
		}
	}

	if (!pIntConstantsArray->USE_OPEN_GL)
	{
		m_pGetWndDX = new CWindowDirectX();

		WindowDirectX::Description Desc;

		Desc.width = 1280;
		Desc.height = 720;
		Desc.caption = L"DirectX Window 11";

		bool success = m_pGetWndDX->Create(Desc);

		if (success)
		{
			// Окно успешно создано, можно начинать обработку сообщений
			while (!m_pGetWndDX->GetIsExit())
			{
				m_pGetWndDX->RunEvent();
			}
		}
	}

#if 0
	//-' LoggerCreate("lesson01.log");

	/*
	pWindowOpenGL = new WindowOpenGL::WindowOpenGL();

	if (!pWindowOpenGL->GLWindowCreate("OpenGL Window", 1280, 720))
		return 1;

	result = pWindowOpenGL->GLWindowMainLoop();

	pWindowOpenGL->GLWindowDestroy();
	delete pWindowOpenGL;
	*/

	//-' LoggerDestroy();
#endif

	delete m_pGetWndDX;

	return result;
}