#include "StdAfx.h"

#include <list>
#include <string>
#include <unordered_set>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <Memory.hpp>
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
#include <Exports.h>

using namespace ShaderPlayground;

#include "Framework.h"
#include "StartUp.hpp"

void Start::Launch() {
    Framework* framework = CreateFrameworkInstance();
    //DX11ViewRender* render = CreateRenderInstance();
    //InputBinder* input = CreateInputBinderInstance(render);

    //Allocator::PrintCollection();

    //FrameworkDesc desc;
    //desc.render = render;
    
    InitializeFramework(framework/*, desc*/);
    //AddInputListenerToFramework(framework, input);
    RunFramework(framework);
    CloseFramework(framework);

    delete framework; // mini hack, rework this

    /*
    DestroyInputBinderInstance(input);
    DestroyRenderInstance(render);
    DestroyFrameworkInstance(framework);
    */
}
