#pragma once

namespace ShaderPlayground {
    struct DescWindow {
    public:
        RENDERLIBRARY_API DescWindow() :
            caption(L""),
            width(640),
            height(480),
            posx(200),
            posy(20),
            resizing(true) {
        }

        int posx;
        int posy;
        std::wstring caption; // заголовок окна
        int width; // ширина клиентской части окна
        int height; // высота клиентской части окна
        bool resizing;
    };

    class Window {
    private:
        static Window* _wndthis;

        DescWindow _desc; // описание окна
        InputManager* _inputmgr;
        HWND _hwnd; // дескриптор окна

        bool _isexit; // флаг сообщающий о событии выхода
        bool _active; // окно активно?
        bool _minimized;
        bool _maximized;
        bool _isresize; // если окно изменило размер

    private:
        void UpdateWindowState();

    public:
        RENDERLIBRARY_API Window();

        RENDERLIBRARY_API static Window* Get() {
            return _wndthis;
        }

        // Создать окно
        RENDERLIBRARY_API bool Create(const DescWindow& desc);

        // Обработка событий окна
        RENDERLIBRARY_API void RunEvent();

        // Закрыть окно.
        RENDERLIBRARY_API void Close();

        RENDERLIBRARY_API void SetInputMgr(InputManager* inputmgr);

        RENDERLIBRARY_API HWND GetHWND() const {
            return _hwnd;
        }
        RENDERLIBRARY_API int GetLeft() const {
            return _desc.posx;
        }
        RENDERLIBRARY_API int GetTop() const {
            return _desc.posy;
        }
        RENDERLIBRARY_API int GetWidth() const {
            return _desc.width;
        }
        RENDERLIBRARY_API int GetHeight() const {
            return _desc.height;
        }

        // Вернуть заголовок окна
        RENDERLIBRARY_API const std::wstring& GetCaption() const {
            return _desc.caption;
        }

        // сообщает, было ли сообщение о выходе
        RENDERLIBRARY_API bool IsExit() const {
            return _isexit;
        }

        // сообщает об активности окна
        RENDERLIBRARY_API bool IsActive() const {
            return _active;
        }

        // сообщает об изменении окна
        // предупреждение: после вызова оповещает окно об обработке события
        RENDERLIBRARY_API bool IsResize() {
            bool ret = _isresize;
            _isresize = false;
            return ret;
        }

        // обработка событий
        RENDERLIBRARY_API LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
    };

    // обработка событий
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
}
