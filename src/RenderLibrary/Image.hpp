#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Image {
    private:
        bool InitBuffers();
        void RenderBuffers();
        void SetShaderParameters(float x, float y);
        void RenderShader();

        Render* _render;

        ID3D11Buffer* _vertexBuffer;
        ID3D11Buffer* _indexBuffer;
        ID3D11Buffer* _constantBuffer;
        Shader* _shader;

        float _bitmapWidth, _bitmapHeight;
        float _previousPosX, _previousPosY;

    public:
        Image(Render* render);

        bool Init(const wchar_t* name, float bitmapWidth, float bitmapHeight);
        void Draw(float positionX, float positionY);
        void Close();
    };
}
