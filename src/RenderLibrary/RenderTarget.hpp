#pragma once

namespace ShaderPlayground {
    class DX11ViewRender;

    class RENDERLIBRARY_API RenderTarget {
    private:
        XMMATRIX _projectionMatrix;
        XMMATRIX _orthoMatrix;
        D3D11_VIEWPORT _viewport;

        DX11ViewRender* _render;

        ID3D11Texture2D* _RTTexture;
        ID3D11Texture2D* _DSTexture;
        ID3D11RenderTargetView* _RTV;
        ID3D11ShaderResourceView* _SRV;
        ID3D11DepthStencilView* _DSV;

    public:
        RenderTarget(DX11ViewRender* render);

        bool Init(float screenNear, float screenDepth);
        void Close();

        void SetRenderTarget();
        void ClearRenderTarget(float, float, float, float);

        // Получаем текстуру RT в виде shader resource view
        ID3D11ShaderResourceView* GetShaderResourceView();

        XMMATRIX GetProjectionMatrix();

        //void* operator new(size_t i) {
        //    return _aligned_malloc(i, 16);
        //}

        //void operator delete(void* p) {
        //    _aligned_free(p);
        //}
    };
}
