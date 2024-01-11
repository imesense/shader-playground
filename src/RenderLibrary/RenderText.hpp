#pragma once

namespace ShaderPlayground
{
    class Text
    {
    public:
        Text(Render* render, BitmapFont* font);

        bool TestInit(const char* text);
        bool Init(const std::wstring& text, int scrW, int scrH);
        void RenderText(float r, float g, float b, float x, float y);
        void Close();

    private:
        bool m_InitBuffers(const std::wstring& text, int scrW, int scrH);
        void m_RenderBuffers();

        Render* m_render;

        BitmapFont* m_font;
        ID3D11Buffer* m_vertexBuffer;
        ID3D11Buffer* m_indexBuffer;
        int m_numindex;
    };
}
