#pragma once

class DirectX11
{
public:
	DirectX11();
	~DirectX11();

	BOOL CreateWindowDirectX11(HWND hWnd);

public:
	D3D11_VIEWPORT viewport;

	DXGI_SWAP_CHAIN_DESC sd;

	ID3D11Device* g_pd3dDevice;
	IDXGISwapChain* g_pSwapChain;

	ID3D11DeviceContext* g_pImmediateContext;
	ID3D11RenderTargetView* g_pRenderTargetView;
};

extern DirectX11* pDirectX11;