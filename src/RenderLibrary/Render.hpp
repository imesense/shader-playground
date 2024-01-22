#pragma once

namespace ShaderPlayground {
    class Render {
        friend class Text;
        friend class BitmapFont;
        friend class Shader;
        
    public:
        Render();
        virtual ~Render();

        bool CreateDevice(HWND hwnd);
        void BeginFrame();
        void EndFrame();
        void Shutdown();

        void TurnZBufferOn();
        void TurnZBufferOff();

        void TurnOnAlphaBlending();
        void TurnOffAlphaBlending();

        ID3D11Device* GetDeviceD3D11()
        {
            return _pd3dDevice;
        }

        ID3D11DeviceContext* GetDeviceD3D11Context()
        {
            return _pImmediateContext;
        }

        XMMATRIX GetOrTho()
        {
            return this->_ortho;
        }

    protected:
        bool Createdevice();
        bool Createdepthstencil();
        void Initmatrix();
        void Resize();

        BitmapFont* m_font;
        Text* text1;
        Text* text2;
        Text* text3;

        RenderState* _renderstate;

        ID3D11Device* _pd3dDevice;
        ID3D11DeviceContext* _pImmediateContext;
        IDXGISwapChain* _pSwapChain;
        ID3D11RenderTargetView* _pRenderTargetView;
        ID3D11DepthStencilView* _pDepthStencilView;

        XMMATRIX _ortho;
        XMMATRIX _projection;

        HWND _hwnd;

        UINT _width = 640;
        UINT _height = 480;

        UINT UVsyncFlag = 0;
    };
}
