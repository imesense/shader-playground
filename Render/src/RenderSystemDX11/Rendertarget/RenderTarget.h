#pragma once

#include "D3D11_Framework.h"

using namespace D3D11View;

class DX11ViewRender;

class RenderTarget
{
public:
	RenderTarget(DX11ViewRender *render);

	bool Init(float screenNear, float screenDepth);
	void Close();

	void SetRenderTarget();
	void ClearRenderTarget(float, float, float, float);
	
	// Получаем текстуру RT в виде shader resource view
	ID3D11ShaderResourceView* GetShaderResourceView();	
	
	XMMATRIX GetProjectionMatrix();

	void* operator new(size_t i)
	{
		return _aligned_malloc(i,16);
	}

	void operator delete(void* p)
	{
		_aligned_free(p);
	}

private:
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_orthoMatrix;
	D3D11_VIEWPORT m_viewport;

	DX11ViewRender* m_render;

	ID3D11Texture2D* m_RTTexture;
	ID3D11Texture2D* m_DSTexture;
	ID3D11RenderTargetView* m_RTV;
	ID3D11ShaderResourceView* m_SRV;
	ID3D11DepthStencilView* m_DSV;
};