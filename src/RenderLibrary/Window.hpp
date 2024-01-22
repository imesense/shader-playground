#pragma once

namespace ShaderPlayground {
    class Window {
    private:
        static Window* _wndthis;

        InputManager* _inputmgr;
        HWND _hwnd; // дескриптор окна

        int posx;
        int posy;

        int width; // ширина клиентской части окна
        int height; // высота клиентской части окна
        bool resizing;

        bool _isexit; // флаг сообщающий о событии выхода
        bool _active; // окно активно?
        bool _minimized;
        bool _maximized;
        bool _isresize; // если окно изменило размер

    private:
        void UpdateWindowState();

    public:
        Window();
        virtual ~Window();

        static Window* Get() {
            return _wndthis;
        }

        bool Create();

        // Обработка событий окна
        void RunEvent();

        // Закрыть окно.
        void Close();

        void SetInputMgr(InputManager* inputmgr);

        HWND GetHWND() const {
            return _hwnd;
        }

        int GetLeft() const {
            return posx;
        }

        int GetTop() const {
            return posy;
        }

        int GetWidth() const {
            return width;
        }

        int GetHeight() const {
            return height;
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
