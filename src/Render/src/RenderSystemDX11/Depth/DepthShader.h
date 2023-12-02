#pragma once

#include "D3D11_Framework.h"

using namespace D3D11View;

class DX11ViewRender;

class DepthShader
{
public:
	DepthShader(DX11ViewRender* render);

	bool Init();
	void Close();
	void Render(int index, CXMMATRIX WVP);

private:
	DX11ViewRender*m_render;

	Shader *m_shader;
	ID3D11Buffer *m_matrixBuffer;
};
