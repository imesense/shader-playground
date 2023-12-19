#pragma once

// InputBinder
extern "C" {
    RENDERLIBRARY_API ShaderPlayground::InputBinder* CreateInputBinderInstance(ShaderPlayground::DX11ViewRender* render);
    RENDERLIBRARY_API void DestroyInputBinderInstance(ShaderPlayground::InputBinder* instance);
}

// DX11ViewRender
extern "C" {
    RENDERLIBRARY_API ShaderPlayground::DX11ViewRender* CreateRenderInstance();
    RENDERLIBRARY_API void DestroyRenderInstance(ShaderPlayground::DX11ViewRender* instance);
}

// Framework
extern "C" {
    RENDERLIBRARY_API ShaderPlayground::Framework* CreateFrameworkInstance();
    RENDERLIBRARY_API void DestroyFrameworkInstance(ShaderPlayground::Framework* instance);

    RENDERLIBRARY_API void InitializeFramework(ShaderPlayground::Framework* instance,
        ShaderPlayground::FrameworkDesc properties);
    RENDERLIBRARY_API void AddInputListenerToFramework(ShaderPlayground::Framework* instance,
        ShaderPlayground::InputListener* listener);

    RENDERLIBRARY_API void RunFramework(ShaderPlayground::Framework* instance);
    RENDERLIBRARY_API void CloseFramework(ShaderPlayground::Framework* instance);
}
