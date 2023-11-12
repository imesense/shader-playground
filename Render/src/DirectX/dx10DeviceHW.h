#pragma once

namespace dx10HW
{
    class DirectX10
    {
    public:
        DirectX10();
        ~DirectX10();

        BOOL CreateWindowDirectX10(HWND hWnd);

    public:
        D3D10_VIEWPORT viewport;

        DXGI_SWAP_CHAIN_DESC sd;
        ID3D10Device* g_pd3dDevice;

        IDXGISwapChain* g_pSwapChain;
        ID3D10RenderTargetView* g_pRenderTargetView;
    };
}

extern dx10HW::DirectX10* pDirectX10;