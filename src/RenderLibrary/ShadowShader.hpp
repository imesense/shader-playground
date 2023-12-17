#pragma once

namespace ShaderPlayground {
    class DX11ViewRender;

    class RENDERLIBRARY_API ShadowShader : public Allocator {
    private:
        DX11ViewRender* _render;
        Shader* _shader;
        ID3D11SamplerState* _sampleStateWrap;
        ID3D11SamplerState* _sampleStateClamp;
        ID3D11Buffer* _matrixBuffer;
        ID3D11Buffer* _lightBuffer;
        ID3D11Buffer* _lightBuffer2;

    public:
        ShadowShader(DX11ViewRender* render);

        bool Init();
        void Close();
        void Render(int indexCount, CXMMATRIX worldMatrix, CXMMATRIX WVP, CXMMATRIX WVPlight,
            ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture,
            Light& light);
    };
}
