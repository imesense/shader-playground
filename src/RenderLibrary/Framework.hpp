#pragma once

namespace ShaderPlayground {
    struct FrameworkDesc {
    public:
        DescWindow wnd;
        Render* render;
    };

    class Framework {
    public:
        RENDERLIBRARY_API Framework();
        RENDERLIBRARY_API ~Framework();

        RENDERLIBRARY_API bool Init(const FrameworkDesc& desc);
        RENDERLIBRARY_API void Run();
        RENDERLIBRARY_API void Close();

        RENDERLIBRARY_API void AddInputListener(InputListener* listener);

    protected:
        bool Frame();

        FrameworkDesc _desc;
        Window* _wnd;
        Render* _render;
        InputManager* _input;
        Log _log;
        bool _init; // если было инициализировано
    };
}

extern "C" {
    RENDERLIBRARY_API ShaderPlayground::Framework* CreateFrameworkInstance() {
        return new ShaderPlayground::Framework();
    }
    RENDERLIBRARY_API void DestroyFrameworkInstance(ShaderPlayground::Framework* instance) {
        delete instance;
    }

    RENDERLIBRARY_API void InitializeFramework(ShaderPlayground::Framework* instance,
        ShaderPlayground::FrameworkDesc properties) {
        instance->Init(properties);
    }

    RENDERLIBRARY_API void AddInputListenerToFramework(ShaderPlayground::Framework* instance,
        ShaderPlayground::InputListener* listener) {
        instance->AddInputListener(listener);
    }

    RENDERLIBRARY_API void RunFramework(ShaderPlayground::Framework* instance) {
        instance->Run();
    }

    RENDERLIBRARY_API void CloseFramework(ShaderPlayground::Framework* instance) {
        instance->Close();
    }
}
