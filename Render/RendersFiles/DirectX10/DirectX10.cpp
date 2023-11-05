#include "..\..\Headers\DirectX10\DirectX10.h"

DirectX10* pDirectX10 = nullptr;

DirectX10::DirectX10()
{
    sd = {};
    g_pd3dDevice = nullptr;
    g_pSwapChain = nullptr;
    g_pRenderTargetView = nullptr;
}

DirectX10::~DirectX10()
{

}

BOOL DirectX10::CreateWindowDirectX10(HWND hWnd)
{
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hWnd;
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
    D3D10_VIEWPORT vp = {};

    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    g_pd3dDevice->RSSetViewports(1, &vp);

    return TRUE;
}
