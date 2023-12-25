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

#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "DepthShader.hpp"
#include "Buffer.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "DX11ViewRender.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "FabricRender.h"

using namespace ShaderPlayground;

//CFabricRender* pCFabricRender = nullptr;

bool CFabricRender::bFabricInit = false;

struct Fabric
{
    Render* pRender;
    DX11ViewRender* pDX11ViewRender;
    InputBinder* pInputBinder;
    Window* pWindow;
    InputManager* pInputManager;
    DepthShader* pDepthShader;
    ShadowShader* pShadowShader;

} fabric;

CFabricRender::CFabricRender()
{
    
}

CFabricRender::~CFabricRender()
{

}

int CFabricRender::CreateFabricRender() {
    Log::Get()->Debug("%s", __FUNCTION__);

    fabric.pDX11ViewRender = new DX11ViewRender();

    if (!fabric.pDX11ViewRender)
    {
        //-' Добавить лог
        return ErrorDescription::E_CREATE_VIEW_RENDER;
    }

    fabric.pDX11ViewRender->Init();

    fabric.pInputBinder = new InputBinder(fabric.pDX11ViewRender);

    if (!fabric.pInputBinder)
    {
        //-' Добавить лог
        return ErrorDescription::E_INPUT_BINDER;
    }

    fabric.pWindow = new Window();

    if (!fabric.pWindow)
    {
        //-' Добавить лог
        return ErrorDescription::E_WINDOW;
    }

    fabric.pInputManager = new InputManager();

    if (!fabric.pInputManager)
    {
        //-' Добавить лог
        return ErrorDescription::E_INPUT_MANAGER;
    }

    //fabric.pInputManager->Initialize();

    fabric.pWindow->Create();

    //fabric.pWindow->SetInputMgr(fabric.pInputManager);

    if (!fabric.pDX11ViewRender->CreateDevice(fabric.pWindow->GetHWND()))
    {
        //-' Добавить лог
        return ErrorDescription::E_CREATE_DEVICE;
    }

    fabric.pDepthShader = new DepthShader(fabric.pDX11ViewRender);

    if (!fabric.pDepthShader)
    {
        //-' Добавить лог
        return ErrorDescription::E_SHADER_DEPTH_INIT;
    }

    fabric.pShadowShader = new ShadowShader(fabric.pDX11ViewRender);

    if (!fabric.pShadowShader)
    {
        //-' Добавить лог
        return ErrorDescription::E_SHADER_SHADOW_INIT;
    }

    const auto AddInputListener = [&](InputListener* listener) -> void
    {
        fabric.pInputManager->AddListener(listener);
    };

    AddInputListener(fabric.pInputBinder);

    this->bFabricInit = true;

    return ErrorDescription::E_OK;
}

bool CFabricRender::RunRender()
{
    if (this->bFabricInit)
    {
        fabric.pWindow->RunEvent();

        if (!fabric.pWindow->IsActive())
        {
            return true;
        }

        if (fabric.pWindow->IsExit())
        {
            return false;
        }

        if (fabric.pWindow->IsResize()) 
        {

        }

        fabric.pDX11ViewRender->BeginFrame();

        if (!fabric.pDX11ViewRender->Draw())
        {
            return false;
        }

        fabric.pDX11ViewRender->EndFrame();
    }

    return true;
}

void CFabricRender::DestroyFabricRender()
{
    if (fabric.pInputManager)
    {
        delete fabric.pInputManager;
        fabric.pInputManager = nullptr;
    }

    if (fabric.pWindow)
    {
        delete fabric.pWindow;
        fabric.pWindow = nullptr;
    }

    if (fabric.pInputBinder)
    {
        delete fabric.pInputBinder;
        fabric.pInputBinder = nullptr;
    }

    if (fabric.pDX11ViewRender)
    {
        delete fabric.pDX11ViewRender;
        fabric.pDX11ViewRender = nullptr;
    }
}
