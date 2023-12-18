#pragma once

namespace ShaderPlayground {
    class InputBinder : public InputListener, public Allocator {
    private:
        DX11ViewRender* _render;

    public:
        RENDERLIBRARY_API InputBinder(DX11ViewRender* render);

        RENDERLIBRARY_API bool KeyPressed(const KeyEvent& arg);
        RENDERLIBRARY_API bool KeyReleased(const KeyEvent& arg);
    };
}

extern "C" {
    RENDERLIBRARY_API ShaderPlayground::InputBinder* CreateInputBinderInstance(ShaderPlayground::DX11ViewRender* render) {
        return new ShaderPlayground::InputBinder(render);
    }
    RENDERLIBRARY_API void DestroyFrameworkInstance(ShaderPlayground::InputBinder* instance) {
        delete instance;
    }
}
