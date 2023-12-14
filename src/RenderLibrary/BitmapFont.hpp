#pragma once

namespace ShaderPlayground {
    struct RENDERLIBRARY_API VertexFont {
        XMFLOAT3 pos;
        XMFLOAT2 tex;
    };

    class RENDERLIBRARY_API BitmapFont {
    private:
        struct CharDesc {
            CharDesc() : srcX(0), srcY(0), srcW(0), srcH(0), xOff(0), yOff(0), xAdv(0) {
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
            XMMATRIX WVP;
        };

        struct PixelBufferType {
            XMFLOAT4 pixelColor;
        };

    public:
        BitmapFont(Render* render);

        bool Init(char* fontFilename);
        void Draw(unsigned int index, float r, float g, float b, float x, float y);
        void BuildVertexArray(VertexFont* vert, int numvert, const wchar_t* sentence);
        void Close();

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
