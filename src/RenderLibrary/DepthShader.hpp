#pragma once

namespace ShaderPlayground {
    class DX11ViewRender;

    class DepthShader {
    private:
        DX11ViewRender* _render;

        Shader* _shader;
        ID3D11Buffer* _matrixBuffer;

    public:
        DepthShader(DX11ViewRender* render);
        virtual ~DepthShader();

        bool Init();
        void Close();
        void Render(int index, CXMMATRIX wvp);
    };
}
