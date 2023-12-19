#include "StdAfx.h"

#include <list>
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "RenderState.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "DepthShader.hpp"
#include "RenderTarget.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "DX11ViewRender.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Log.hpp"
#include "Framework.hpp"
#include "Exports.h"
#include "Helpers.h"

using namespace ShaderPlayground;

// InputBinder
RENDERLIBRARY_API InputBinder* CreateInputBinderInstance(DX11ViewRender* render) {
    return new InputBinder(render);
}
RENDERLIBRARY_API void DestroyInputBinderInstance(InputBinder* instance) {
    _DELETE(instance);
}

// DX11ViewRender
RENDERLIBRARY_API DX11ViewRender* CreateRenderInstance() {
    return new DX11ViewRender();
}
RENDERLIBRARY_API void DestroyRenderInstance(DX11ViewRender* instance) {
    delete instance;
}

// Framework
RENDERLIBRARY_API Framework* CreateFrameworkInstance() {
    return new Framework();
}
RENDERLIBRARY_API void DestroyFrameworkInstance(Framework* instance) {
    delete instance;
}

RENDERLIBRARY_API void InitializeFramework(Framework* instance, FrameworkDesc properties) {
    instance->Init(properties);
}
RENDERLIBRARY_API void AddInputListenerToFramework(Framework* instance, InputListener* listener) {
    instance->AddInputListener(listener);
}

RENDERLIBRARY_API void RunFramework(Framework* instance) {
    instance->Run();
}
RENDERLIBRARY_API void CloseFramework(Framework* instance) {
    instance->Close();
}
