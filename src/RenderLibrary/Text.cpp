#include "StdAfx.h"

#include <map>
#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "RenderState.hpp"
#include "Render.hpp"
#include "Text.hpp"
#include "Shader.hpp"
#include "BitmapFont.hpp"
#include "Buffer.hpp"
#include "Helpers.h"

using namespace ShaderPlayground;

Text::Text(Render* render, BitmapFont* font) {
    _render = render;
    _font = font;
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    _numindex = 0;
    _numdrawindex = 0;
    _numvertex = 0;
    _static = true;
    _size = 0;
}

bool Text::Init(const std::wstring& text, bool statictext, int charsize) {
    _static = statictext;
    _size = charsize;

    if (!InitBuffers(text)) {
        return false;
    }
    return true;
}

bool Text::InitBuffers(const std::wstring& text) {
    if (!_size || (_size < text.size())) {
        _size = text.size();
    }

    _numvertex = _size * 4;
    _numindex = _size * 6;
    _numdrawindex = text.size() * 6;
    if (_numdrawindex > _numindex) {
        _numdrawindex = _numindex;
    }

    VertexFont* vertex = new VertexFont[_numvertex];
    if (!vertex) {
        return false;
    }

    unsigned long* indices = new unsigned long[_numindex];
    if (!indices) {
        return false;
    }

    _font->BuildVertexArray(vertex, _numvertex, text.c_str());

    for (int i = 0; i < _numindex / 6; i++) {
        indices[i * 6 + 0] = i * 4 + 0;
        indices[i * 6 + 1] = i * 4 + 1;
        indices[i * 6 + 2] = i * 4 + 2;
        indices[i * 6 + 3] = i * 4 + 0;
        indices[i * 6 + 4] = i * 4 + 3;
        indices[i * 6 + 5] = i * 4 + 1;
    }

    _vertexBuffer = Buffer::CreateVertexBuffer(_render->_pd3dDevice, sizeof(VertexFont) * _numvertex, !_static, vertex);
    if (!_vertexBuffer) {
        return false;
    }

    _indexBuffer = Buffer::CreateIndexBuffer(_render->_pd3dDevice, sizeof(unsigned long) * _numindex, false, indices);
    if (!_indexBuffer) {
        return false;
    }

    _DELETE_ARRAY(vertex);
    _DELETE_ARRAY(indices);

    return true;
}

bool Text::Updatebuffer(const std::wstring& text) {
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT result = _render->_pImmediateContext->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) {
        return false;
    }

    VertexFont* verticesPtr = (VertexFont*) mappedResource.pData;
    _font->BuildVertexArray(verticesPtr, _numvertex, text.c_str());
    _render->_pImmediateContext->Unmap(_vertexBuffer, 0);

    return true;
}

void Text::Draw(float r, float g, float b, float x, float y) {
    RenderBuffers();
    _font->Draw(_numdrawindex, r, g, b, x, y);
}

void Text::RenderBuffers() {
    unsigned int stride = sizeof(VertexFont);
    unsigned int offset = 0;
    _render->_pImmediateContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    _render->_pImmediateContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //_render->_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Text::Close() {
    _RELEASE(_vertexBuffer);
    _RELEASE(_indexBuffer);
}

bool Text::SetText(const std::wstring& text) {
    // статический текст нельзя изменить
    if (_static) {
        return false;
    }

    // если текст меньше чем число индексов, мы не должны рисовать ненужные
    _numdrawindex = text.size() * 6;
    return Updatebuffer(text);
}
