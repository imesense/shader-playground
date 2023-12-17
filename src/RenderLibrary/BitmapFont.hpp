#pragma once

namespace ShaderPlayground {
    struct VertexFont {
    public:
        XMFLOAT3 pos;
        XMFLOAT2 tex;
    };

    class BitmapFont {
    private:
        struct CharDesc {
        public:
            RENDERLIBRARY_API CharDesc() : srcX(0), srcY(0), srcW(0), srcH(0), xOff(0), yOff(0), xAdv(0) {
            }

            short srcX;
            short srcY;
            short srcW;
            short srcH;
            short xOff;
            short yOff;
            short xAdv;
        };

        struct ConstantBuffer {
        public:
            XMMATRIX WVP;
        };

        struct PixelBufferType {
        public:
            XMFLOAT4 pixelColor;
        };

    public:
        RENDERLIBRARY_API BitmapFont(Render* render);

        RENDERLIBRARY_API bool Init(char* fontFilename);
        RENDERLIBRARY_API void Draw(unsigned int index, float r, float g, float b, float x, float y);
        RENDERLIBRARY_API void BuildVertexArray(VertexFont* vert, int numvert, const wchar_t* sentence);
        RENDERLIBRARY_API void Close();

    private:
        bool Parse(char* fontFilename);
        void SetShaderParameters(float r, float g, float b, float x, float y);

        Render* _render;
        ID3D11Buffer* _constantBuffer;
        ID3D11Buffer* _pixelBuffer;
        Shader* _shader;

        unsigned short _widthTex;
        unsigned short _heightTex;

        std::wstring _file;
        std::map<int, CharDesc> _chars;
    };
}
