#pragma once

namespace ShaderPlayground {
    class RenderState {
    private:
        ID3D11Device* _pd3dDevice;
        ID3D11DeviceContext* _pImmediateContext;

        ID3D11DepthStencilState* _pDepthEnableStencilState;
        ID3D11DepthStencilState* _pDepthDisabledStencilState;
        ID3D11BlendState* _pAlphaEnableBlendingState;
        ID3D11BlendState* _pAlphaDisableBlendingState;

        ID3D11SamplerState* _pSampleState;

        bool _depthenable;
        bool _alphaenable;

    private:
        bool Createdepthstencilstate();
        bool Createblendingstate();
        bool Createsamplerstate();

    public:
        RenderState();
        virtual ~RenderState();

        RenderState(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

        bool Init();
        void Close();

        void TurnZBufferOn();
        void TurnZBufferOff();

        void TurnOnAlphaBlending();
        void TurnOffAlphaBlending();
    };
}
