#pragma once

namespace ShaderPlayground {
    class Framework {
    public:
        RENDERLIBRARY_API Framework();
        RENDERLIBRARY_API ~Framework();
        RENDERLIBRARY_API bool Init();

        RENDERLIBRARY_API void Run();
        RENDERLIBRARY_API void Close();

        RENDERLIBRARY_API void AddInputListener(InputListener* listener);

    protected:
        bool Frame();

        Window* _wnd;
        Render* _render;
        InputManager* _input;
        Log _log;
        bool _init; // если было инициализировано
    };
}
