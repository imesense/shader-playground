#include "stdafx.h"
#include "dx10DeviceHW.h"

dx10HW::DirectX10* pDirectX10 = nullptr;

namespace dx10HW
{
    DirectX10::DirectX10()
    {
        sd = {};
        viewport = {};

        g_pd3dDevice = nullptr;
        g_pSwapChain = nullptr;

        g_pRenderTargetView = nullptr;
    }

    DirectX10::~DirectX10()
    {

    }

    BOOL DirectX10::CreateWindowDirectX10(HWND hWnd)
    {
        RECT rc;
        HRESULT hr = S_OK;

        GetClientRect(hWnd, &rc);

        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 2;
        sd.OutputWindow = hWnd;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.Windowed = TRUE;

        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;

        D3D10_DRIVER_TYPE driverType = D3D10_DRIVER_TYPE_HARDWARE;

        hr = D3D10CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, D3D10_SDK_VERSION, &sd,
            &g_pSwapChain, &g_pd3dDevice);

        if (FAILED(hr))
            return FALSE;

        // Создаем Render Target View
        ID3D10Texture2D* pBackBuffer = nullptr;
        hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);

        if (FAILED(hr))
            return FALSE;

        hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);

        pBackBuffer->Release();

        if (FAILED(hr))
            return FALSE;

        g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

        // Устанавливаем окно Viewport
        viewport.Width = width;
        viewport.Height = height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;

        g_pd3dDevice->RSSetViewports(1, &viewport);

        return TRUE;
    }
}