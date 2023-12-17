#pragma once


namespace ShaderPlayground {
    class RENDERLIBRARY_API DX11ViewRender : public Render, public Allocator {
    private:
        friend DepthShader;
        friend RenderTarget;
        friend ShadowShader;
        friend class MyInput;

        Camera _cam;
        Light _Light;

        RenderTarget* _RenderTexture;
        DepthShader* _DepthShader;
        ShadowShader* _ShadowShader;

        D3D11_VIEWPORT _viewport;

        // индексный и вершинный буферы для ящика и поверхности
        ID3D11Buffer* _vb_ground;
        ID3D11Buffer* _ib_ground;
        ID3D11Buffer* _vb_box;
        ID3D11Buffer* _ib_box;

        // текстуры
        ID3D11ShaderResourceView* _texture_ground;
        ID3D11ShaderResourceView* _texture_box1;
        ID3D11ShaderResourceView* _texture_box2;

        // позиции первого и второго ящика
        XMFLOAT3 _posbox1;
        XMFLOAT3 _posbox2;

    public:
        bool _key_up;
        bool _key_down;
        bool _key_left;
        bool _key_right;
        bool _key_a;
        bool _key_z;
        bool _key_s;
        bool _key_x;

    public:
        DX11ViewRender();

        bool Init();
        bool Draw();
        void Close();

        void RenderSceneToTexture();
        void RenderSceneToWindow();
    };
}
