#include "StdAfx.h"

#include <list>
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <InputCodes.hpp>
#include <InputManager.hpp>
#include <Window.hpp>
#include <RenderState.hpp>
#include <Render.hpp>
#include <Log.hpp>
#include <Framework.hpp>
#include <DepthShader.hpp>
#include <RenderTarget.hpp>
#include <Light.hpp>
#include <ShadowShader.hpp>
#include <Timer.hpp>
#include <Camera.hpp>
#include <DX11ViewRender.hpp>
#include <InputListener.hpp>
#include <InputBinder.hpp>

#include "Framework.h"
#include "Program.h"

using namespace ShaderPlayground;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    int result = -1;

    Framework framework;

    DX11ViewRender* render = new DX11ViewRender();
    InputBinder* input = new InputBinder(render);

    FrameworkDesc desc;
    desc.render = render;

    framework.Init(desc);
    framework.AddInputListener(input);
    framework.Run();
    framework.Close();

    return result;
}
