#include "StdAfx.h"

#include <list>
#include <string>
#include <unordered_set>
#include <d3d11.h>
#include <DirectXMath.h>

#include "RenderDebugUtils.h"

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "RenderState.hpp"
#include "Render.hpp"
#include "Log.hpp"
#include "Framework.hpp"
#include "Helpers.h"

//#include "Memory.hpp"
//#include "RenderState.hpp"
//#include "Render.hpp"
#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "DepthShader.hpp"
#include "Buffer.hpp"
//#include "Helpers.h"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "DX11ViewRender.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"

using namespace ShaderPlayground;

Framework::Framework() :
    _wnd(nullptr),
    _render(nullptr),
    _input(nullptr),
    _init(false) {
}

Framework::~Framework() {
}

void Framework::AddInputListener(InputListener* listener) {
    Log::Get()->Debug("%s", __FUNCTION__);
    if (_input) {
        _input->AddListener(listener);
    }
}

#ifdef ONLY_RENDER
bool Framework::Init() 
#else
bool Framework::Init(window_handle hwnd, int width, int height)
#endif
{
    Log::Get()->Debug("%s", __FUNCTION__);

    DX11ViewRender* render = new DX11ViewRender();
    InputBinder* input = new InputBinder(render);

    _render = render;

    _wnd = new Window();
    _input = new InputManager();

    _input->Initialize();

#ifdef ONLY_RENDER
    if (!_wnd->Create(/*desc.wnd*/)) {
        Log::Get()->Err("Не удалось создать окно");
        return false;
    }
#else
    _wnd->CreateHWND(hwnd, width, height);
#endif

    _wnd->SetInputMgr(_input);

    if (!_render->CreateDevice(_wnd->GetHWND())) {
        Log::Get()->Err("Не удалось создать рендер");
        return false;
    }

    _init = true;

    AddInputListener(input);

    return true;
}

void Framework::Run() {
    if (_init) {
        while (Frame());
    }
}

bool Framework::Frame()
{
    // обрабатываем события окна
    _wnd->RunEvent();
    // если окно неактивно - завершаем кадр
    if (!_wnd->IsActive()) {
        return true;
    }

    // если окно было закрыто, завершаем работу движка
    if (_wnd->IsExit()) {
        return false;
    }

    // если окно изменило размер
    if (_wnd->IsResize()) {
    }

    _render->BeginFrame();
    if (!_render->Draw()) {
        return false;
    }
    _render->EndFrame();

    return true;
}

void Framework::Close()
{
    _init = false;
    _render->Shutdown();

    _DELETE(_render);
    _CLOSE(_wnd);
    _CLOSE(_input);
}
