#include "StdAfx.h"

#include <fstream>
#include <vector>

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <ms3dspec.h>

#include "RenderState.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "StaticMesh.hpp"
#include "Buffer.hpp"
#include "Helpers.h"

using namespace ShaderPlayground;

struct Vertex {
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct ConstantBuffer {
    XMMATRIX WVP;
};

StaticMesh::StaticMesh(Render* render) {
    _render = render;
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    _constantBuffer = nullptr;
    _shader = nullptr;
}

bool StaticMesh::Init(wchar_t* name) {
    Identity();

    _shader = new Shader(_render);
    if (!_shader) {
        return false;
    }

    _shader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
    _shader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);

    wchar_t vertexShader[] = L"mesh.vs";
    wchar_t pixelShader[] = L"mesh.ps";

    if (!_shader->CreateShader(vertexShader, pixelShader)) {
        return false;
    }

    if (!LoadMS3DFile(name)) {
        return false;
    }

    return true;
}

bool StaticMesh::LoadMS3DFile(wchar_t* Filename) {
    unsigned short VertexCount = 0;
    unsigned short TriangleCount = 0;
    unsigned short GroupCount = 0;
    unsigned short MaterialCount = 0;

    MS3DVertex* pMS3DVertices = nullptr;
    MS3DTriangle* pMS3DTriangles = nullptr;
    MS3DGroup* pMS3DGroups = nullptr;
    MS3DMaterial* pMS3DMaterials = nullptr;
    MS3DHeader header{};

    std::ifstream fin;

    fin.open(Filename, std::ios::binary);
    fin.read((char*)(&(header)), sizeof(header));
    if (header.version != 3 && header.version != 4) {
        return false;
    }

    fin.read((char*)(&VertexCount), sizeof(unsigned short));
    pMS3DVertices = new MS3DVertex[VertexCount];
    fin.read((char*)pMS3DVertices, VertexCount * sizeof(MS3DVertex));

    fin.read((char*)(&TriangleCount), sizeof(unsigned short));
    pMS3DTriangles = new MS3DTriangle[TriangleCount];
    fin.read((char*)pMS3DTriangles, TriangleCount * sizeof(MS3DTriangle));

    fin.read((char*)(&GroupCount), sizeof(unsigned short));
    pMS3DGroups = new MS3DGroup[GroupCount];
    for (int i = 0; i < GroupCount; i++) {
        fin.read((char*)&(pMS3DGroups[i].flags), sizeof(unsigned char));
        fin.read((char*)&(pMS3DGroups[i].name), sizeof(char[32]));
        fin.read((char*)&(pMS3DGroups[i].numtriangles), sizeof(unsigned short));
        unsigned short triCount = pMS3DGroups[i].numtriangles;
        pMS3DGroups[i].triangleIndices = new unsigned short[triCount];
        fin.read((char*)(pMS3DGroups[i].triangleIndices), sizeof(unsigned short) * triCount);
        fin.read((char*)&(pMS3DGroups[i].materialIndex), sizeof(char));
    }

    fin.read((char*)(&MaterialCount), sizeof(unsigned short));
    pMS3DMaterials = new MS3DMaterial[MaterialCount];
    fin.read((char*)pMS3DMaterials, MaterialCount * sizeof(MS3DMaterial));

    fin.close();

    _indexCount = TriangleCount * 3;
    unsigned short* indices = new unsigned short[_indexCount];
    if (!indices) {
        return false;
    }

    Vertex* vertices = new Vertex[VertexCount];
    if (!vertices) {
        return false;
    }

    for (int i = 0; i < TriangleCount; i++) {
        indices[3 * i + 0] = pMS3DTriangles[i].vertexIndices[0];
        indices[3 * i + 1] = pMS3DTriangles[i].vertexIndices[1];
        indices[3 * i + 2] = pMS3DTriangles[i].vertexIndices[2];
    }

    for (int i = 0; i < VertexCount; i++) {
        vertices[i].Pos.x = pMS3DVertices[i].vertex[0];
        vertices[i].Pos.y = pMS3DVertices[i].vertex[1];
        vertices[i].Pos.z = pMS3DVertices[i].vertex[2];

        for (int j = 0; j < TriangleCount; j++) {
            if (i == pMS3DTriangles[j].vertexIndices[0]) {
                vertices[i].Tex.x = pMS3DTriangles[j].s[0];
                vertices[i].Tex.y = pMS3DTriangles[j].t[0];
            } else if (i == pMS3DTriangles[j].vertexIndices[1]) {
                vertices[i].Tex.x = pMS3DTriangles[j].s[1];
                vertices[i].Tex.y = pMS3DTriangles[j].t[1];
            } else if (i == pMS3DTriangles[j].vertexIndices[2]) {
                vertices[i].Tex.x = pMS3DTriangles[j].s[2];
                vertices[i].Tex.y = pMS3DTriangles[j].t[2];
            } else {
                continue;
            }
            break;
        }
    }

    wchar_t* name = CharToWChar(pMS3DMaterials[0].texture);
    if (!_shader->AddTexture(name)) {
        return false;
    }
    _DELETE_ARRAY(name);

    _DELETE_ARRAY(pMS3DMaterials);
    if (pMS3DGroups != nullptr) {
        for (int i = 0; i < GroupCount; i++) {
            _DELETE_ARRAY(pMS3DGroups[i].triangleIndices);
        }
        _DELETE_ARRAY(pMS3DGroups);
    }
    _DELETE_ARRAY(pMS3DTriangles);
    _DELETE_ARRAY(pMS3DVertices);

    _vertexBuffer = Buffer::CreateVertexBuffer(_render->_pd3dDevice, sizeof(Vertex) * VertexCount, false, vertices);
    if (!_vertexBuffer) {
        return false;
    }

    _indexBuffer = Buffer::CreateIndexBuffer(_render->_pd3dDevice, sizeof(unsigned short) * _indexCount, false, indices);
    if (!_indexBuffer) {
        return false;
    }

    _constantBuffer = Buffer::CreateConstantBuffer(_render->_pd3dDevice, sizeof(ConstantBuffer), false);
    if (!_constantBuffer) {
        return false;
    }

    _DELETE_ARRAY(vertices);
    _DELETE_ARRAY(indices);

    return true;
}

void StaticMesh::Draw(CXMMATRIX viewmatrix) {
    RenderBuffers();
    SetShaderParameters(viewmatrix);
    RenderShader();
}

void StaticMesh::RenderBuffers()
{
    unsigned int stride = sizeof(Vertex);
    unsigned int offset = 0;
    _render->_pImmediateContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    _render->_pImmediateContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
    /*_render->_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/
}

void StaticMesh::SetShaderParameters(CXMMATRIX viewmatrix) {
    XMMATRIX WVP = _objMatrix * viewmatrix * _render->_projection;
    ConstantBuffer cb{};
    cb.WVP = XMMatrixTranspose(WVP);
    _render->_pImmediateContext->UpdateSubresource(_constantBuffer, 0, NULL, &cb, 0, 0);
    _render->_pImmediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
}

void StaticMesh::RenderShader() {
    _shader->Draw();
    _render->_pImmediateContext->DrawIndexed(_indexCount, 0, 0);
}

void StaticMesh::Close() {
    _RELEASE(_indexBuffer);
    _RELEASE(_vertexBuffer);
    _RELEASE(_constantBuffer);
    _CLOSE(_shader);
}

void StaticMesh::Translate(float x, float y, float z) {
    _objMatrix *= XMMatrixTranslation(x, y, z);
}

void StaticMesh::Rotate(float angle, float x, float y, float z) {
    XMVECTOR v = XMVectorSet(x, y, z, 0.0f);
    _objMatrix *= XMMatrixRotationAxis(v, angle);
}

void StaticMesh::Scale(float x, float y, float z) {
    _objMatrix *= XMMatrixScaling(x, y, z);
}

void StaticMesh::Identity() {
    _objMatrix = XMMatrixIdentity();
}
