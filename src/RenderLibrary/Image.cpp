#include "StdAfx.h"

#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"

#include "RenderState.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Buffer.hpp"
#include "Helpers.h"

using namespace ShaderPlayground;

struct Vertex {
    XMFLOAT3 pos;
    XMFLOAT2 tex;
};

struct ConstantBuffer {
    XMMATRIX Ortho;
};

Image::Image(Render* render) {
    _render = render;
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    _constantBuffer = nullptr;
    _shader = nullptr;
}

bool Image::Init(const wchar_t* textureFilename, float bitmapWidth, float bitmapHeight) {
    _bitmapWidth = bitmapWidth;
    _bitmapHeight = bitmapHeight;
    _previousPosX = -1;
    _previousPosY = -1;

    if (!InitBuffers()) {
        return false;
    }

    _shader = new Shader(_render);
    if (!_shader) {
        return false;
    }
    if (!_shader->AddTexture(textureFilename)) {
        return false;
    }

    _shader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
    _shader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);

    char vertexShader[] = "image.vs";
    char pixelShader[] = "image.ps";

    if (!_shader->CreateShader(vertexShader, pixelShader)) {
        return false;
    }

    return true;
}

bool Image::InitBuffers() {
    Vertex vertices[4]{};

    signed int centreW = _render->_width / 2 * -1;
    signed int centreH = _render->_height / 2;
    float left = (float) centreW;
    float right = left + _bitmapWidth;
    float top = (float)centreH;
    float bottom = top - _bitmapHeight;

    vertices[0].pos = XMFLOAT3(left, top, 0.0f);
    vertices[0].tex = XMFLOAT2(0.0f, 0.0f);

    vertices[1].pos = XMFLOAT3(right, bottom, 0.0f);
    vertices[1].tex = XMFLOAT2(1.0f, 1.0f);

    vertices[2].pos = XMFLOAT3(left, bottom, 0.0f);
    vertices[2].tex = XMFLOAT2(0.0f, 1.0f);

    vertices[3].pos = XMFLOAT3(right, top, 0.0f);
    vertices[3].tex = XMFLOAT2(1.0f, 0.0f);

    unsigned long indices[6] = {
        0,1,2,
        0,3,1
    };

    _vertexBuffer = Buffer::CreateVertexBuffer(_render->_pd3dDevice, sizeof(Vertex) * 4, false, &vertices);
    if (!_vertexBuffer) {
        return false;
    }

    _indexBuffer = Buffer::CreateIndexBuffer(_render->_pd3dDevice, sizeof(unsigned long) * 6, false, &indices);
    if (!_indexBuffer) {
        return false;
    }

    _constantBuffer = Buffer::CreateConstantBuffer(_render->_pd3dDevice, sizeof(ConstantBuffer), false);
    if (!_constantBuffer) {
        return false;
    }

    return true;
}

void Image::Draw(float positionX, float positionY) {
    RenderBuffers();
    SetShaderParameters(positionX, positionY);
    RenderShader();
}

void Image::RenderBuffers()
{
    unsigned int stride = sizeof(Vertex);
    unsigned int offset = 0;
    _render->_pImmediateContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    _render->_pImmediateContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //_render->_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Image::SetShaderParameters(float x, float y) {
    XMMATRIX objmatrix = XMMatrixTranslation(x, -y, 0.0f);
    XMMATRIX wvp = objmatrix * _render->_ortho;
    ConstantBuffer cb;
    cb.Ortho = XMMatrixTranspose(wvp);
    _render->_pImmediateContext->UpdateSubresource(_constantBuffer, 0, NULL, &cb, 0, 0);
    _render->_pImmediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
}

void Image::RenderShader() {
    _shader->Draw();
    _render->_pImmediateContext->DrawIndexed(6, 0, 0);
}

void Image::Close() {
    _RELEASE(_vertexBuffer);
    _RELEASE(_indexBuffer);
    _RELEASE(_constantBuffer);
    _CLOSE(_shader);
}
