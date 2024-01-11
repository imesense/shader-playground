#include "StdAfx.h"

#include <list>
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>
#include <fstream> // Для использования std::ifstream
#include <iostream> // Для использования std::getline
#include <unordered_set>
#include <vector>
#include <map>
#include <d3d11.h>
#include <D3DX11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
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
#include "BitmapFont.h"
#include "RenderText.hpp"

using namespace ShaderPlayground;

Text::Text(Render* render, BitmapFont* font)
{
	m_render = render;
	m_font = font;
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_numindex = 0;
}

bool Text::TestInit(const char* text)
{
    pLog->Write("TestInit: ", "%s", text);

    return true;
}

bool Text::Init(const std::wstring& text, int screenWidth, int screenHeight)
{
	if (!m_InitBuffers(text, screenWidth, screenHeight))
		return false;

	return true;
}

bool Text::m_InitBuffers(const std::wstring& text, int screenWidth, int screenHeight)
{
	int vertnum = text.size() * 6;
	VertexFont* vertex = new VertexFont[vertnum];
	if (!vertex)
		return false;

	m_font->BuildVertexArray(vertex, text.c_str(), screenWidth, screenHeight);

	m_numindex = text.size() * 6;
	unsigned long* indices = new unsigned long[m_numindex];

	for (int i = 0; i < m_numindex; i++)
		indices[i] = i;

	HRESULT result;
	D3D11_BUFFER_DESC BufferDesc;
	D3D11_SUBRESOURCE_DATA Data;

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(VertexFont) * vertnum;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	Data.pSysMem = vertex;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	result = m_render->GetDeviceD3D11()->CreateBuffer(&BufferDesc, &Data, &m_vertexBuffer);
	if (FAILED(result))
		return false;

	BufferDesc.ByteWidth = sizeof(unsigned long) * m_numindex;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	Data.pSysMem = indices;

	result = m_render->GetDeviceD3D11()->CreateBuffer(&BufferDesc, &Data, &m_indexBuffer);
	if (FAILED(result))
		return false;

	_DELETE_ARRAY(vertex);
	_DELETE_ARRAY(indices);

	return true;
}

void Text::RenderText(float r, float g, float b, float x, float y)
{
	m_RenderBuffers();
	m_font->RenderBitmapFont(m_numindex, r, g, b, x, y);
}

void Text::Close()
{
	_RELEASE(m_vertexBuffer);
	_RELEASE(m_indexBuffer);
}

void Text::m_RenderBuffers()
{
	unsigned int stride = sizeof(VertexFont);
	unsigned int offset = 0;
	m_render->GetDeviceD3D11Context()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	m_render->GetDeviceD3D11Context()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_render->GetDeviceD3D11Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
