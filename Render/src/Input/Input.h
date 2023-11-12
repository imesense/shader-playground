#pragma once
#include "InputSDK.h"
#include "InputEvent.h"

namespace Input
{
	class InputEvents;

	class CInput
	{
	public:
		void Init();
		void Close();

		void Run(const UINT &msg, WPARAM wParam, LPARAM lParam);

		void AddListener(InputEvents*Listener);

		// зона окна
		void SetWinRect(const RECT &winrect);

	private:
		// событие движения мыши
		void m_eventcursor();
		// событие кнопки мыши
		void m_eventmouse(const eMouseKeyCodes KeyCode, bool press);
		// событие вращения колесика
		void m_mousewheel(short Value);
		// обработка события клавиши
		void m_eventkey(const eKeyCodes KeyCode, const wchar_t ch, bool press);

		std::list<InputEvents*> m_Listener;

		RECT m_windowrect;
		int m_curx;
		int m_cury;
		int m_MouseWheel;
	};
}