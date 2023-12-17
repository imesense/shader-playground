#include "StdAfx.h"

#include <list>
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <unordered_set>
#include "Memory.hpp"

#include "InputCodes.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "RenderState.hpp"
#include "Render.hpp"
#include "Log.hpp"
#include "Framework.hpp"
#include "Helpers.h"

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
    if (_input) {
        _input->AddListener(listener);
    }
}

bool Framework::Init(const FrameworkDesc& desc) {
    _render = desc.render;

    _wnd = new Window();
    _input = new InputManager();

    _input->Initialize();

    if (!_wnd->Create(desc.wnd)) {
        Log::Get()->Err("Не удалось создать окно");
        return false;
    }
    _wnd->SetInputMgr(_input);

    if (!_render->CreateDevice(_wnd->GetHWND())) {
        Log::Get()->Err("Не удалось создать рендер");
        return false;
    }

    _init = true;
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
