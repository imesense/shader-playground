#include "stdafx.h"
#include "Frame/Framework.h"
//#include "MyRender.h"
//#include "MyInput.h"

#include "InputSystem/InputOverride.h"

using namespace D3D11View;
//#include "Constants/Constants.h"
//#include "Utils/ManagerKeys.h"
//#include "OpenGL/CreateWindowGL.h"
//#include "DirectX/CreateWindowDX.h"
//#include "Allocator/Allocator.h"

//using namespace Constants;
//using namespace Utils;
//using namespace DirectXOBJECT;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	int result = -1;

	Framework framework;

	DX11ViewRender* render = new DX11ViewRender();
	MyInput* input = new MyInput(render);

	FrameworkDesc desc;
	desc.render = render;

	framework.Init(desc);
	framework.AddInputListener(input);
	framework.Run();
	framework.Close();

	//pIntConstantsArray = new IntConstantsArray();
	//pCommandLineArguments = new CommandLineArguments();

	//for (std::string& key : keys)
	//{
	//	if (key == "-use_dx10" && pCommandLineArguments->CheckKey(key))
	//	{
	//		pIntConstantsArray->USE_DX10 = true;
	//		result = 0;
	//	}

	//	if (key == "-use_dx11" && pCommandLineArguments->CheckKey(key))
	//	{
	//		pIntConstantsArray->USE_DX11 = true;
	//		result = 1;
	//	}

	//	if (key == "-use_open_gl" && pCommandLineArguments->CheckKey(key))
	//	{
	//		pIntConstantsArray->USE_OPEN_GL = true;
	//		result = 2;
	//	}
	//}

	//if (!pIntConstantsArray->USE_OPEN_GL)
	//{
	//	m_pGetWndDX = new CWindowDirectX();

	//	DirectXOBJECT::Description Desc;

	//	Desc.width = 1280;
	//	Desc.height = 720;
	//	Desc.caption = pIntConstantsArray->USE_DX11 ? L"DirectX11 Window" : L"DirectX10 Window";

	//	bool success = m_pGetWndDX->Create(Desc, pIntConstantsArray->USE_DX11);

	//	if (success)
	//	{
	//		// Окно успешно создано, можно начинать обработку сообщений
	//		while (!m_pGetWndDX->GetIsExit())
	//		{
	//			m_pGetWndDX->RunEvent();
	//		}
	//	}
	//}
	//else
	//{
	////-' LoggerCreate("lesson01.log");

	//	pWindowOpenGL = new WindowOpenGL::WindowOpenGL();

	//	if (!pWindowOpenGL->GLWindowCreate("OpenGL Window", 1280, 720))
	//		return 1;

	//	result = pWindowOpenGL->GLWindowMainLoop();

	//	pWindowOpenGL->GLWindowDestroy();
	//	delete pWindowOpenGL;

	////-' LoggerDestroy();
	//}

	//delete m_pGetWndDX;

	return result;
}