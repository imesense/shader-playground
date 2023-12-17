#pragma once

namespace ShaderPlayground {
    class Text {
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
        RENDERLIBRARY_API Text(Render* render, BitmapFont* font);

        // text - текст который нужно вывести
        // static - если true, то данный текст нельзя изменить
        // size - максимальное количество букв которые можно вывести. 0 означает что это число равно размеру text
        RENDERLIBRARY_API bool Init(const std::wstring& text, bool statictext = true, int charsize = 0);
        RENDERLIBRARY_API void Draw(float r, float g, float b, float x, float y);
        RENDERLIBRARY_API void Close();

        RENDERLIBRARY_API bool SetText(const std::wstring& text);
    };
}
