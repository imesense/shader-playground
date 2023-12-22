#pragma once

// Framework
extern "C" {
    RENDERLIBRARY_API ShaderPlayground::Framework* CreateFrameworkInstance();
    RENDERLIBRARY_API void DestroyFrameworkInstance(ShaderPlayground::Framework* instance);

#ifdef ONLY_RENDER
    RENDERLIBRARY_API void InitializeFramework(ShaderPlayground::Framework* instance);
#else
    RENDERLIBRARY_API void InitializeFramework(ShaderPlayground::Framework* instance, window_handle hwnd = NULL);
#endif

    RENDERLIBRARY_API void RunFramework(ShaderPlayground::Framework* instance);
    RENDERLIBRARY_API void CloseFramework(ShaderPlayground::Framework* instance);
}

