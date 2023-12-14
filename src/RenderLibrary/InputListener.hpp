#pragma once

#include "InputCodes.hpp"

namespace ShaderPlayground {
    // События мыши
    struct RENDERLIBRARY_API MouseEvent {
        MouseEvent(int nx, int ny) : x(nx), y(ny) {
        }

        // Координаты мыши
        int x;
        int y;
    };

    // событие нажатия кнопки мыши
    struct RENDERLIBRARY_API MouseEventClick : public MouseEvent {
        MouseEventClick(MouseKeyCodes b, int nx, int ny) : MouseEvent(nx, ny), btn(b) {}

        const MouseKeyCodes btn; // Клавиша
    };

    // событие прокрутки мыши
    struct RENDERLIBRARY_API MouseEventWheel : public MouseEvent {
        MouseEventWheel(int nwheel, int nx, int ny) : MouseEvent(nx, ny), wheel(nwheel) {}

        int wheel;
    };

    // событие клавиши
    struct RENDERLIBRARY_API KeyEvent {
        KeyEvent(wchar_t c, KeyCodes kc) : wc(c), code(kc) {}

        const wchar_t wc;
        const KeyCodes code;
    };

    class RENDERLIBRARY_API InputListener {
    public:
        // если методы возращают true - событие больше никем не обрабатывается

        // кнопка нажата
        virtual bool MousePressed(const MouseEventClick& arg) {
            return false;
        }
        // кнопка отпущена
        virtual bool MouseReleased(const MouseEventClick& arg) {
            return false;
        }
        // вращение колесика
        virtual bool MouseWheel(const MouseEventWheel& arg) {
            return false;
        }
        // движение мыши
        virtual bool MouseMove(const MouseEvent& arg) {
            return false;
        }

        // кнопка нажата
        virtual bool KeyPressed(const KeyEvent& arg) {
            return false;
        }
        // кнопка отпущена
        virtual bool KeyReleased(const KeyEvent& arg) {
            return false;
        }
    };
}
