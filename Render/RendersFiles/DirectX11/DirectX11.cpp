#include "stdafx.h"
#include "Headers/DirectX11/DirectX11.h"

DirectX11* pDirectX11 = nullptr;

DirectX11::DirectX11()
{
    sd = {};
    viewport = {};

    g_pd3dDevice = nullptr;
    g_pSwapChain = nullptr;

    g_pImmediateContext = nullptr;
    g_pRenderTargetView = nullptr;
}

DirectX11::~DirectX11()
{

}

BOOL DirectX11::CreateWindowDirectX11(HWND hWnd)
{ 
   HRESULT hr = S_OK;
   RECT rc;
   GetClientRect(hWnd, &rc);
   UINT width = rc.right - rc.left;
   UINT height = rc.bottom - rc.top;

   UINT createDeviceFlags = 0;

#ifdef _DEBUG
   createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

   D3D_DRIVER_TYPE driverTypes[] =
   {
       D3D_DRIVER_TYPE_HARDWARE,
       D3D_DRIVER_TYPE_WARP,
       D3D_DRIVER_TYPE_REFERENCE,
   };

   UINT numDriverTypes = ARRAYSIZE(driverTypes);

   D3D_FEATURE_LEVEL featureLevels[] =
   {
       D3D_FEATURE_LEVEL_11_0,
       D3D_FEATURE_LEVEL_10_1,
       D3D_FEATURE_LEVEL_10_0,
   };

   UINT numFeatureLevels = ARRAYSIZE(featureLevels);

   for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
   {
       g_pd3dDevice = nullptr;
       g_pImmediateContext = nullptr;

       hr = D3D11CreateDevice(nullptr, driverTypes[driverTypeIndex], nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
           D3D11_SDK_VERSION, &g_pd3dDevice, nullptr, &g_pImmediateContext);

       if (SUCCEEDED(hr))
           break;
   }

   if (FAILED(hr))
       return FALSE;

   // Создаем Swap Chain
   sd.BufferCount = 1;
   sd.BufferDesc.Width = width;
   sd.BufferDesc.Height = height;
   sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   sd.BufferDesc.RefreshRate.Numerator = 60;
   sd.BufferDesc.RefreshRate.Denominator = 1;
   sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   sd.OutputWindow = hWnd;
   sd.SampleDesc.Count = 1;
   sd.SampleDesc.Quality = 0;
   sd.Windowed = TRUE;

   hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
       D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, nullptr, &g_pImmediateContext);

   if (FAILED(hr))
       return FALSE;

   // Создаем Render Target View
   ID3D11Texture2D* pBackBuffer = nullptr;
   hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

   if (FAILED(hr))
       return FALSE;

   hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);

   pBackBuffer->Release();

   if (FAILED(hr))
       return FALSE;

   g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

   // Устанавливаем окно Viewport
   viewport.Width = static_cast<FLOAT>(width);
   viewport.Height = static_cast<FLOAT>(height);
   viewport.MinDepth = 0.0f;
   viewport.MaxDepth = 1.0f;
   viewport.TopLeftX = 0;
   viewport.TopLeftY = 0;

   g_pImmediateContext->RSSetViewports(1, &viewport);

   return TRUE;
}

