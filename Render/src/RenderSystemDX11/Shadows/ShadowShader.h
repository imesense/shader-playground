#pragma once

#include "D3D11_Framework.h"
#include "../Light/Light.h"

using namespace D3D11View;

class DX11ViewRender;

class ShadowShader
{
public:
	ShadowShader(DX11ViewRender*render);

	bool Init();
	void Close();
	void Render(int indexCount, CXMMATRIX worldMatrix, CXMMATRIX WVP, CXMMATRIX WVPlight, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture, Light &light);
	
private:
	DX11ViewRender*m_render;
	Shader *m_shader;
	ID3D11SamplerState* m_sampleStateWrap;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_lightBuffer2;
};