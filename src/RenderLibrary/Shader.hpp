#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Shader {
    private:
        Render* _render;

        ID3D11VertexShader* _vertexShader;
        ID3D11PixelShader* _pixelShader;
        ID3D11InputLayout* _layout;
        std::vector<ID3D11ShaderResourceView*> _textures;
        D3D11_INPUT_ELEMENT_DESC* _layoutformat;
        unsigned int _numlayout;

    private:
        HRESULT Compileshaderfromfile(char* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** ppBlobOut);

    public:
        Shader(Render* render);

        // данную функцию мы должны вызывать до вызова CreateShader
        void AddInputElementDesc(const char* SemanticName, DXGI_FORMAT format);
        void AddInputElementDesc(const char* SemanticName, unsigned int SemanticIndex, DXGI_FORMAT format,
            unsigned int InputSlot = 0, bool AlignedByteOffset = true,
            D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            unsigned int InstanceDataStepRate = 0);

        bool CreateShader(char* namevs, char* nameps);
        bool AddTexture(const wchar_t* name);

        void Draw();
        void Close();
    };
}
