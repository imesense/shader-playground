#include "StdAfx.h"

/* Disable rarely used windows stuff */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <list>
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "RenderState.hpp"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <wrl/client.h>
#include <string>
#include "RenderText.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "DepthShader.hpp"
#include "RenderTarget.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "DX11ViewRender.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Exports.hpp"
#include "Helpers.hpp"
#include "../MultiLogManager/Exports.hpp"
#include "../MultiLogManager/Log/Log.hpp"
#include "FabricDirectXWindow.hpp"

using namespace ShaderPlayground;

CRenderText* CRenderText::_getInstance = nullptr;

CRenderText::CRenderText(ID3D11Device* device, ID3D11DeviceContext* context, unsigned screenWidth, unsigned screenHeight)
{
    spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
    spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"new_font.spritefont");
    commonStates = std::make_unique<DirectX::CommonStates>(device);

    SetScreenSize(screenWidth, screenHeight);

    this->_getInstance = this;
}

CRenderText::~CRenderText()
{

}

void CRenderText::SetScreenSize(unsigned screenWidth, unsigned screenHeight)
{
    screenRect.left = 0;
    screenRect.top = 0;
    screenRect.right = static_cast<LONG>(screenWidth);
    screenRect.bottom = static_cast<LONG>(screenHeight);
}

void CRenderText::DrawTextR(const wchar_t* text, DirectX::XMFLOAT2 position, DirectX::FXMVECTOR color,
    float rotation, DirectX::XMFLOAT2 origin, float scale,
    DirectX::SpriteEffects effects, float layerDepth)
{
    spriteBatch->Begin();
    spriteFont->DrawString(spriteBatch.get(), text, position, color, rotation, origin, scale, effects, layerDepth);
    spriteBatch->End();
}
