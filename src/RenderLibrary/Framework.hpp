#pragma once

namespace ShaderPlayground {
    //struct FrameworkDesc {
    //public:
    //    DescWindow wnd;
    //    Render* render;
    //};

    class Framework {
    public:
        RENDERLIBRARY_API Framework();
        RENDERLIBRARY_API ~Framework();
#ifdef ONLY_RENDER
        RENDERLIBRARY_API bool Init();
#else
        RENDERLIBRARY_API bool Init(window_handle hwnd);
#endif

        RENDERLIBRARY_API void Run();
        RENDERLIBRARY_API void Close();

        RENDERLIBRARY_API void AddInputListener(InputListener* listener);

    protected:
        bool Frame();

        /*FrameworkDesc _desc;*/
        Window* _wnd;
        Render* _render;
        InputManager* _input;
        Log _log;
        bool _init; // если было инициализировано
    };
}
