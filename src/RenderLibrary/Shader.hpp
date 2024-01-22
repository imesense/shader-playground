#pragma once

namespace ShaderPlayground {
    class Shader {
    private:
        Render* _render;

        ID3D11VertexShader* _vertexShader;
        ID3D11PixelShader* _pixelShader;
        ID3D11InputLayout* _layout;
        std::vector<ID3D11ShaderResourceView*> _textures;
        D3D11_INPUT_ELEMENT_DESC* _layoutformat;
        unsigned int _numlayout;

    public:
        Shader(Render* render);
        virtual ~Shader();

        void AddInputElementDesc(const char* SemanticName, DXGI_FORMAT format);
        void AddInputElementDesc(const char* SemanticName, unsigned int SemanticIndex, DXGI_FORMAT format,
            unsigned int InputSlot = 0, bool AlignedByteOffset = true,
            D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            unsigned int InstanceDataStepRate = 0);

        HRESULT Compileshaderfromfile(const char* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** ppBlobOut);

        bool CreateShader(const char* namevs, const char* nameps);
        bool AddTexture(const wchar_t* name);

        void Draw();
        void Close();
    };
}
