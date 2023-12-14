#include "StdAfx.h"

#include <d3d11.h>

#include "Buffer.hpp"

using namespace ShaderPlayground;

ID3D11Buffer* Buffer::CreateVertexBuffer(ID3D11Device* device, int size, bool dynamic, const void* mem) {
    ID3D11Buffer* vb = nullptr;

    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = size;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    if (dynamic) {
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    } else {
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = 0;
    }

    D3D11_SUBRESOURCE_DATA data{};
    data.pSysMem = mem;
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    HRESULT hr = device->CreateBuffer(&bufferDesc, &data, &vb);
    if (FAILED(hr)) {
        return nullptr;
    }

    return vb;
}

ID3D11Buffer* Buffer::CreateIndexBuffer(ID3D11Device* device, int size, bool dynamic, const void* mem) {
    ID3D11Buffer* ib = nullptr;

    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = size;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    if (dynamic) {
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    } else {
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = 0;
    }

    D3D11_SUBRESOURCE_DATA data{};
    data.pSysMem = mem;
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    HRESULT hr = device->CreateBuffer(&bufferDesc, &data, &ib);
    if (FAILED(hr)) {
        return nullptr;
    }

    return ib;
}

ID3D11Buffer* Buffer::CreateConstantBuffer(ID3D11Device* device, int size, bool dynamic) {
    ID3D11Buffer* cb = nullptr;

    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = size;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    if (dynamic) {
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    } else {
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = 0;
    }

    HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &cb);
    if (FAILED(hr)) {
        return nullptr;
    }

    return cb;
}
