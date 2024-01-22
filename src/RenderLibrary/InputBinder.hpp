#pragma once

namespace ShaderPlayground {
    class DX11ViewRender;

    class InputBinder : public InputListener, public Allocator {
    private:
        DX11ViewRender* _render;

    public:
        InputBinder(DX11ViewRender* render);
        virtual ~InputBinder();

        bool KeyPressed(const KeyEvent& arg);
        bool KeyReleased(const KeyEvent& arg);
    };
}
