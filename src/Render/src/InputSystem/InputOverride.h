#pragma once

#include "D3D11_Framework.h"
#include "..\RenderSystemDX11\RenderView\RenderView.h"

using namespace D3D11View;

class MyInput : public InputListener
{
public:
	MyInput(DX11ViewRender*render);

	bool KeyPressed(const KeyEvent &arg);
	bool KeyReleased(const KeyEvent &arg);

private:
	DX11ViewRender*m_render;
};