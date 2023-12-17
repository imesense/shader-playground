#include "StdAfx.h"

#include <list>
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
#include <unordered_set>
#include "Memory.hpp"

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
using namespace ShaderPlayground;

#include "StartUp.hpp"

void Start::Launch() {
    Framework framework;

    DX11ViewRender* render = new DX11ViewRender();

    InputBinder* input = new InputBinder(render);

    Allocator::PrintCollection();

    FrameworkDesc desc;
    desc.render = render;
    
    framework.Init(desc);
    framework.AddInputListener(input);
    framework.Run();
    framework.Close();
}
