#pragma once

namespace ShaderPlayground {
    class DX11ViewRender;

    class RENDERLIBRARY_API DepthShader {
    private:
        DX11ViewRender* _render;

        Shader* _shader;
        ID3D11Buffer* _matrixBuffer;

    public:
        DepthShader(DX11ViewRender* render);

        bool Init();
        void Close();
        void Render(int index, CXMMATRIX wvp);
    };
}
