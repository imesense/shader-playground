#pragma once

namespace ShaderPlayground
{
    class CRenderText
    {
    public:
        CRenderText(ID3D11Device* device, ID3D11DeviceContext* context, unsigned screenWidth, unsigned screenHeight);
        virtual ~CRenderText();

        void SetScreenSize(unsigned screenWidth, unsigned screenHeight);
        void DrawTextR(const wchar_t* text, DirectX::XMFLOAT2 position, DirectX::FXMVECTOR color = DirectX::Colors::White,
            float rotation = 0, DirectX::XMFLOAT2 origin = DirectX::XMFLOAT2(0, 0), float scale = 1,
            DirectX::SpriteEffects effects = DirectX::SpriteEffects_None, float layerDepth = 0);

        static CRenderText* GetRenderTextInstance()
        {
            return _getInstance;
        }

    private:
        RECT screenRect;

        static CRenderText* _getInstance;

        std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
        std::unique_ptr<DirectX::SpriteFont> spriteFont;
        std::unique_ptr<DirectX::CommonStates> commonStates;
    };

    //extern ShaderPlayground::CRenderText* _instance;
}
