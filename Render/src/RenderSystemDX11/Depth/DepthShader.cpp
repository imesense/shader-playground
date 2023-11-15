#include "stdafx.h"
#include "DepthShader.h"
#include "..\RenderView\RenderView.h"

struct MatrixBufferType
{
	XMMATRIX WVP;
};

DepthShader::DepthShader(DX11ViewRender* render)
{
	m_shader = nullptr;
	m_matrixBuffer = nullptr;
	m_render = render;
}

bool DepthShader::Init()
{
	// инициализируем шейдер и входной формат
	m_shader = new Shader(m_render);
	m_shader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);

	wchar_t vertexShader[] = L"depth.vs";
	wchar_t pixelShader[] = L"depth.ps";

	if ( !m_shader->CreateShader(vertexShader, pixelShader) )
		return false;

	// создаем константный буфер
	m_matrixBuffer = Buffer::CreateConstantBuffer(m_render->m_pd3dDevice, sizeof(MatrixBufferType), false);

	return true;
}

void DepthShader::Render(int index, CXMMATRIX WVP)
{
	MatrixBufferType cb;

	cb.WVP = XMMatrixTranspose(WVP);
	m_render->m_pImmediateContext->UpdateSubresource(m_matrixBuffer, 0, NULL, &cb, 0, 0);
	m_render->m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	m_shader->Draw();	
	m_render->m_pImmediateContext->DrawIndexed(index, 0, 0);
}


void DepthShader::Close()
{
	_CLOSE(m_shader);
	_RELEASE(m_matrixBuffer);
}