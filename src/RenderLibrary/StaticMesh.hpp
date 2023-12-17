#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API StaticMesh {
    private:
        Render* _render;

        ID3D11Buffer* _vertexBuffer;
        ID3D11Buffer* _indexBuffer;
        ID3D11Buffer* _constantBuffer;
        Shader* _shader;

        XMMATRIX _objMatrix;
        unsigned short _indexCount;

    private:
        bool LoadMS3DFile(wchar_t* name);

        void RenderBuffers();
        void SetShaderParameters(CXMMATRIX viewmatrix);
        void RenderShader();

    public:
        StaticMesh(Render* render);

        bool Init(wchar_t* name);
        void Draw(CXMMATRIX viewmatrix);
        void Close();

        void Translate(float x, float y, float z);
        void Rotate(float angle, float x, float y, float z);
        void Scale(float x, float y, float z);
        void Identity();


        //void* operator new(size_t i) {
        //    return _aligned_malloc(i, 16);
        //}

        //void operator delete(void* p) {
        //    _aligned_free(p);
        //}
    };
}
