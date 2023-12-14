#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API InputBinder : public InputListener {
    private:
        DX11ViewRender* _render;

    public:
        InputBinder(DX11ViewRender* render);

        bool KeyPressed(const KeyEvent& arg);
        bool KeyReleased(const KeyEvent& arg);
    };
}
