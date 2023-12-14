#pragma once

namespace ShaderPlayground {
    struct RENDERLIBRARY_API DescWindow {
        DescWindow() :
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

    class RENDERLIBRARY_API Window {
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
        Window();

        static Window* Get() {
            return _wndthis;
        }

        // Создать окно
        bool Create(const DescWindow& desc);

        // Обработка событий окна
        void RunEvent();

        // Закрыть окно.
        void Close();

        void SetInputMgr(InputManager* inputmgr);

        HWND GetHWND() const {
            return _hwnd;
        }
        int GetLeft() const {
            return _desc.posx;
        }
        int GetTop() const {
            return _desc.posy;
        }
        int GetWidth() const {
            return _desc.width;
        }
        int GetHeight() const {
            return _desc.height;
        }

        // Вернуть заголовок окна
        const std::wstring& GetCaption() const {
            return _desc.caption;
        }

        // сообщает, было ли сообщение о выходе
        bool IsExit() const {
            return _isexit;
        }

        // сообщает об активности окна
        bool IsActive() const {
            return _active;
        }

        // сообщает об изменении окна
        // предупреждение: после вызова оповещает окно об обработке события
        bool IsResize() {
            bool ret = _isresize;
            _isresize = false;
            return ret;
        }

        // обработка событий
        LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
    };

    // обработка событий
    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
}
