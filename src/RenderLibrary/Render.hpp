#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Render {
        friend class StaticMesh;
        friend class Image;
        friend class BitmapFont;
        friend class Text;
        friend class Shader;

    public:
        Render();
        virtual ~Render();

        bool CreateDevice(HWND hwnd);
        void BeginFrame();
        void EndFrame();
        void Shutdown();

        virtual bool Init() = 0;
        virtual bool Draw() = 0;
        virtual void Close() = 0;

        void TurnZBufferOn();
        void TurnZBufferOff();

        void TurnOnAlphaBlending();
        void TurnOffAlphaBlending();

        void* operator new(size_t i) {
            return _aligned_malloc(i, 16);
        }

        void operator delete(void* p) {
            _aligned_free(p);
        }

    protected:
        bool Createdevice();
        bool Createdepthstencil();
        void Initmatrix();
        void Resize();

        RenderState* _renderstate;

        ID3D11Device* _pd3dDevice;
        ID3D11DeviceContext* _pImmediateContext;
        IDXGISwapChain* _pSwapChain;
        ID3D11RenderTargetView* _pRenderTargetView;
        ID3D11DepthStencilView* _pDepthStencilView;

        XMMATRIX _ortho;
        XMMATRIX _projection;

        HWND _hwnd;

        unsigned int _width;
        unsigned int _height;
    };
}
