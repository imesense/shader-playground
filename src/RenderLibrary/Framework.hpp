#pragma once

namespace ShaderPlayground {
    struct RENDERLIBRARY_API FrameworkDesc {
        DescWindow wnd;
        Render* render;
    };

    class RENDERLIBRARY_API Framework {
    public:
        Framework();
        ~Framework();

        bool Init(const FrameworkDesc& desc);
        void Run();
        void Close();

        void AddInputListener(InputListener* listener);

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
