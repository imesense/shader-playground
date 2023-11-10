#pragma once

namespace WindowDirectX
{
	struct Description
	{
		Description() :
			caption(L""),
			width(1280),
			height(720),
			posx(200),
			posy(20),
			resizing(true)
		{}

		int posx;
		int posy;

		std::wstring caption;

		int width;
		int height;

		bool resizing;
	};

	class CWindowDirectX
	{
	public:
		CWindowDirectX();
		~CWindowDirectX();

		void RunEvent();
		void Close();

		bool Create(const Description& desc);

		Description* GetWndDescr() { return &WndDescr; };
		static CWindowDirectX* GetWndDX() { return m_GetWndDX11; }

		void SetIsExit(bool value)  { m_isexit = value; }
		bool GetIsExit() const { return m_isexit; }

		void SetActive(bool value) { m_active = value; }
		bool GetActive() const { return m_active; }

		void SetResize(bool value) { m_isresize = value; }
		bool GetResize() const { return m_isresize; }

		void SetMinimized(bool value) { m_minimized = value; }
		bool GetMinimized() const { return m_minimized; }

		void SetMaximized(bool value) { m_maximized = value; }
		bool GetMaximized() const { return m_maximized; }

		bool IsResize()
		{
			bool ret = m_isresize;
			m_isresize = false;
			return ret;
		}

		void m_UpdateWindowState();

		void UpdatePosition(int x, int y)
		{
			WndDescr.posx = x;
			WndDescr.posy = y;
		}

		void UpdateSizeWindow(int x, int y)
		{
			WndDescr.width = x;
			WndDescr.height = y;
		}

		bool CheckNotRsizing() { return !WndDescr.resizing; };

	private:
		Description WndDescr;

		static CWindowDirectX* m_GetWndDX11;

		bool m_isexit;
		bool m_active;
		bool m_minimized;
		bool m_maximized;
		bool m_isresize;

	protected:
		HWND m_hWnd;
		WNDCLASSEXW WndCls;
	};

	class CWindowDirectX11Properyes
	{
		friend class CWindowDirectX11;

	};
}

extern WindowDirectX::CWindowDirectX* m_pGetWndDX;