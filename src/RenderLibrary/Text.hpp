#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Text {
    private:
        Render* _render;

        BitmapFont* _font;
        ID3D11Buffer* _vertexBuffer;
        ID3D11Buffer* _indexBuffer;
        int _numindex;
        int _numdrawindex;
        int _numvertex;

        bool _static;
        int _size;

    private:
        bool InitBuffers(const std::wstring& text);
        void RenderBuffers();
        bool Updatebuffer(const std::wstring& text);

    public:
        Text(Render* render, BitmapFont* font);

        // text - текст который нужно вывести
        // static - если true, то данный текст нельзя изменить
        // size - максимальное количество букв которые можно вывести. 0 означает что это число равно размеру text
        bool Init(const std::wstring& text, bool statictext = true, int charsize = 0);
        void Draw(float r, float g, float b, float x, float y);
        void Close();

        bool SetText(const std::wstring& text);
    };
}
