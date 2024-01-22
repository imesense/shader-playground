#include "StdAfx.h"

#include <list>
#include <sstream>
#include <string>
#include <fstream> // Для использования std::ifstream
#include <iostream> // Для использования std::getline
#include <unordered_set>
#include <filesystem>
#include <vector>
#include <map>
#include <d3d11.h>
#include <D3DX11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "Utils.hpp"
#include "InputCodes.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "RenderState.hpp"
#include <wrl/client.h>

#include "Render.hpp"
#include "Helpers.hpp"

#include "Shader.hpp"
#include "RenderTarget.hpp"
#include "DepthShader.hpp"
#include "Buffer.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "DX11ViewRender.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "FabricRender.hpp"
#include "../MultiLogManager/Exports.hpp"
#include "../MultiLogManager/Log/Log.hpp"
#include "BitmapFont.hpp"
#include "RenderText.hpp"

using namespace ShaderPlayground;

BitmapFont::BitmapFont(Render* render)
{
	m_render = render;
	m_texture = nullptr;
	m_constantBuffer = nullptr;
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_layout = nullptr;
	m_sampleState = nullptr;
	m_pixelBuffer = nullptr;
	m_WidthTex = 0;
	m_HeightTex = 0;
}

BitmapFont::~BitmapFont()
{

}

bool BitmapFont::Init(const char* fontFilename)
{
    pLog->Write("Init", "[%s]: %s", __FUNCTION__, fontFilename);

	if (!m_parse(fontFilename))
		return false;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFileW(m_render->GetDeviceD3D11(), m_file.c_str(), NULL, NULL, &m_texture, NULL);
	if (FAILED(hr))
		return false;

	const char* vertexShader = "bitmapfont.vs";
	const char* pixelShader = "bitmapfont.ps";

	std::string vsPath = CombinedPathForResources(vertexShader);
	std::string psPath = CombinedPathForResources(pixelShader);

    pLog->Write("Init Shader", "[%s]: %s", __FUNCTION__, vsPath.c_str());
    pLog->Write("Init Shader", "[%s]: %s", __FUNCTION__, psPath.c_str());

    if (!m_InitShader(vsPath.c_str(), psPath.c_str()))
    {
        pLog->Write("Not found shaders", "[%s]", __FUNCTION__);
        return false;
    }

    pLog->Write("Init", "[%s]: OK", __FUNCTION__);

	return true;
}

bool BitmapFont::m_parse(const char* fontFilename)
{
	std::ifstream fin{};
	fin.open(fontFilename);
	if (fin.fail())
		return false;

	std::string Line;
	std::string Read, Key, Value;
	size_t i;
	while (!fin.eof())
	{
		std::stringstream LineStream;
		std::getline(fin, Line);
		LineStream << Line;

		LineStream >> Read;
		if (Read == "common")
		{
			while (!LineStream.eof())
			{
				std::stringstream Converter{};
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				Converter << Value;
				if (Key == "scaleW")
					Converter >> m_WidthTex;
				else if (Key == "scaleH")
					Converter >> m_HeightTex;
			}
		}
		else if (Read == "page")
		{
			while (!LineStream.eof())
			{
				std::stringstream Converter{};
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				std::string str;
				Converter << Value;
				if (Key == "file")
				{
					Converter >> str;

                    auto l_CharToWChar = [&](char* mbString) -> wchar_t*
                    {
                        int len = 0;
                        len = (int)strlen(mbString) + 1;
                        wchar_t* ucString = new wchar_t[len];
                        mbstowcs(ucString, mbString, len);
                        return ucString;
                    };

					wchar_t* name = l_CharToWChar((char*)str.substr(1, Value.length() - 2).c_str());
					m_file = name;
                    deleteArray(name);
				}
			}
		}
		else if (Read == "char")
		{
			unsigned short CharID = 0;
			CharDesc chard;

			while (!LineStream.eof())
			{
				std::stringstream Converter{};
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				Converter << Value;
				if (Key == "id")
					Converter >> CharID;
				else if (Key == "x")
					Converter >> chard.srcX;
				else if (Key == "y")
					Converter >> chard.srcY;
				else if (Key == "width")
					Converter >> chard.srcW;
				else if (Key == "height")
					Converter >> chard.srcH;
				else if (Key == "xoffset")
					Converter >> chard.xOff;
				else if (Key == "yoffset")
					Converter >> chard.yOff;
				else if (Key == "xadvance")
					Converter >> chard.xAdv;
			}
			m_Chars.insert(std::pair<int, CharDesc>(CharID, chard));
		}
	}

	fin.close();

	return true;
}

bool BitmapFont::m_InitShader(const char* vsFilename, const char* psFilename)
{
    ID3DBlob* pixelShaderBuffer = nullptr;
	ID3DBlob* vertexShaderBuffer = nullptr;

	HRESULT result = _shader->Compileshaderfromfile(vsFilename, "VS", "vs_4_0", &vertexShaderBuffer);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: vs shader: %s", __FUNCTION__, vsFilename);
        return false;
    }

	result = _shader->Compileshaderfromfile(psFilename, "PS", "ps_4_0", &pixelShaderBuffer);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: ps shader: %s", __FUNCTION__, psFilename);
        return false;
    }

	result = m_render->GetDeviceD3D11()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: CreateVertexShader", __FUNCTION__);
        return false;
    }

	result = m_render->GetDeviceD3D11()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: CreatePixelShader", __FUNCTION__);
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC polygonLayout[2]{};
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;
	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = m_render->GetDeviceD3D11()->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: m_render->GetDeviceD3D11()->CreateInputLayout", __FUNCTION__);
        return false;
    }

    ReleasePtr(vertexShaderBuffer);
    ReleasePtr(pixelShaderBuffer);

    D3D11_BUFFER_DESC BufferDesc{};
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(ConstantBuffer);
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	result = m_render->GetDeviceD3D11()->CreateBuffer(&BufferDesc, NULL, &m_constantBuffer);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: m_render->GetDeviceD3D11()->CreateBuffer", __FUNCTION__);
        return false;
    }

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(PixelBufferType);
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	result = m_render->GetDeviceD3D11()->CreateBuffer(&BufferDesc, NULL, &m_pixelBuffer);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: m_render->GetDeviceD3D11()->CreateBuffer", __FUNCTION__);
        return false;
    }

    D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = m_render->GetDeviceD3D11()->CreateSamplerState(&samplerDesc, &m_sampleState);

    if (FAILED(result))
    {
        pLog->Write("Error", "[%s]: m_render->GetDeviceD3D11()->CreateSamplerState", __FUNCTION__);
        return false;
    }

	return true;
}

void BitmapFont::BuildVertexArray(VertexFont* vertices, const wchar_t* sentence, int screenWidth, int screenHeight)
{
	int numLetters = (int)wcslen(sentence);

	float drawX = (float)-screenWidth / 2;
	float drawY = (float)screenHeight / 2;

	int index = 0;

	for (int i = 0; i < numLetters; i++)
	{
		float CharX = m_Chars[sentence[i]].srcX;
		float CharY = m_Chars[sentence[i]].srcY;
		float Width = m_Chars[sentence[i]].srcW;
		float Height = m_Chars[sentence[i]].srcH;
		float OffsetX = m_Chars[sentence[i]].xOff;
		float OffsetY = m_Chars[sentence[i]].yOff;

		float left = drawX + OffsetX;
		float right = left + Width;
		float top = drawY - OffsetY;
		float bottom = top - Height;
		float lefttex = CharX / m_WidthTex;
		float righttex = (CharX + Width) / m_WidthTex;
		float toptex = CharY / m_HeightTex;
		float bottomtex = (CharY + Height) / m_HeightTex;

		vertices[index].pos = XMFLOAT3(left, top, 0.0f);
		vertices[index].tex = XMFLOAT2(lefttex, toptex);
		index++;
		vertices[index].pos = XMFLOAT3(right, bottom, 0.0f);
		vertices[index].tex = XMFLOAT2(righttex, bottomtex);
		index++;
		vertices[index].pos = XMFLOAT3(left, bottom, 0.0f);
		vertices[index].tex = XMFLOAT2(lefttex, bottomtex);
		index++;
		vertices[index].pos = XMFLOAT3(left, top, 0.0f);
		vertices[index].tex = XMFLOAT2(lefttex, toptex);
		index++;
		vertices[index].pos = XMFLOAT3(right, top, 0.0f);
		vertices[index].tex = XMFLOAT2(righttex, toptex);
		index++;
		vertices[index].pos = XMFLOAT3(right, bottom, 0.0f);
		vertices[index].tex = XMFLOAT2(righttex, bottomtex);
		index++;

		drawX += m_Chars[sentence[i]].xAdv;
	}
}

void BitmapFont::RenderBitmapFont(unsigned int index, float r, float g, float b, float x, float y)
{
	m_SetShaderParameters(r, g, b, x, y);
	m_RenderShader(index);
}

void BitmapFont::m_SetShaderParameters(float r, float g, float b, float x, float y)
{
	XMMATRIX objmatrix = XMMatrixTranslation(x, -y, 0);
	XMMATRIX wvp = objmatrix * m_render->GetOrTho();
	ConstantBuffer cb;
	cb.WVP = XMMatrixTranspose(wvp);
	m_render->GetDeviceD3D11Context()->UpdateSubresource(m_constantBuffer, 0, NULL, &cb, 0, 0);

	m_render->GetDeviceD3D11Context()->VSSetConstantBuffers(0, 1, &m_constantBuffer);

	m_render->GetDeviceD3D11Context()->PSSetShaderResources(0, 1, &m_texture);

	PixelBufferType pb;
	pb.pixelColor = XMFLOAT4(r, g, b, 1.0f);
	m_render->GetDeviceD3D11Context()->UpdateSubresource(m_pixelBuffer, 0, NULL, &pb, 0, 0);

	m_render->GetDeviceD3D11Context()->PSSetConstantBuffers(0, 1, &m_pixelBuffer);
}

void BitmapFont::m_RenderShader(unsigned int index)
{
	m_render->GetDeviceD3D11Context()->IASetInputLayout(m_layout);
	m_render->GetDeviceD3D11Context()->VSSetShader(m_vertexShader, NULL, 0);
	m_render->GetDeviceD3D11Context()->PSSetShader(m_pixelShader, NULL, 0);
	m_render->GetDeviceD3D11Context()->PSSetSamplers(0, 1, &m_sampleState);
	m_render->GetDeviceD3D11Context()->DrawIndexed(index, 0, 0);
}

void BitmapFont::Close()
{
    ReleasePtr(m_constantBuffer);
    ReleasePtr(m_pixelBuffer);
    ReleasePtr(m_vertexShader);
    ReleasePtr(m_pixelShader);
    ReleasePtr(m_layout);
    ReleasePtr(m_sampleState);
    ReleasePtr(m_texture);

    pLog->Write("Memory", "%p, %p, %p, %p, %p, %p", m_constantBuffer, m_pixelBuffer, m_vertexShader, m_pixelShader, m_layout, m_sampleState, m_texture);
}
