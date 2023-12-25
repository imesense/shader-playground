#include "StdAfx.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "RenderState.hpp"
#include "Render.hpp"
#include "Shader.hpp"
#include "BitmapFont.hpp"
#include "Buffer.hpp"
#include "Helpers.h"
#include "Log.hpp"

using namespace ShaderPlayground;

BitmapFont::BitmapFont(Render* render) {
    _render = render;
    _constantBuffer = nullptr;
    _pixelBuffer = nullptr;
    _shader = nullptr;
    _widthTex = 0;
    _heightTex = 0;
}

bool BitmapFont::Init(char* fontFilename) {
    //Log::Get()->Debug("%s", __FUNCTION__);

    if (!Parse(fontFilename)) {
        return false;
    }

    _shader = new Shader(_render);
    if (!_shader) {
        return false;
    }

    if (!_shader->AddTexture(_file.c_str())) {
        return false;
    }

    _shader->AddInputElementDesc("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
    _shader->AddInputElementDesc("TEXCOORD", DXGI_FORMAT_R32G32_FLOAT);

    char vertexShader[] = "BitmapFont.vs";
    char pixelShader[] = "BitmapFont.ps";

    if (!_shader->CreateShader(vertexShader, pixelShader)) {
        return false;
    }

    _constantBuffer = Buffer::CreateConstantBuffer(_render->_pd3dDevice, sizeof(ConstantBuffer), false);
    if (!_constantBuffer) {
        return false;
    }

    _pixelBuffer = Buffer::CreateConstantBuffer(_render->_pd3dDevice, sizeof(PixelBufferType), false);
    if (!_pixelBuffer) {
        return false;
    }

    return true;
}

bool BitmapFont::Parse(char* fontFilename) {
    std::ifstream fin;
    fin.open(fontFilename);
    if (fin.fail()) {
        return false;
    }

    std::string line;
    std::string read, key, value;
    size_t i;
    while (!fin.eof()) {
        std::stringstream lineStream;
        std::getline(fin, line);
        lineStream << line;

        lineStream >> read;
        if (read == "common") {
            while (!lineStream.eof()) {
                std::stringstream converter;
                lineStream >> read;
                i = read.find('=');
                key = read.substr(0, i);
                value = read.substr(i + 1);

                converter << value;
                if (key == "scaleW") {
                    converter >> _widthTex;
                } else if (key == "scaleH") {
                    converter >> _heightTex;
                }
            }
        } else if (read == "page") {
            while (!lineStream.eof()) {
                std::stringstream converter;
                lineStream >> read;
                i = read.find('=');
                key = read.substr(0, i);
                value = read.substr(i + 1);

                std::string str;
                converter << value;
                if (key == "file") {
                    converter >> str;
                    wchar_t* name = CharToWChar((char*) str.substr(1, value.length() - 2).c_str());
                    _file = name;
                    _DELETE_ARRAY(name);
                }
            }
        } else if (read == "char") {
            unsigned short charID = 0;
            CharDesc chard;

            while (!lineStream.eof()) {
                std::stringstream converter;
                lineStream >> read;
                i = read.find('=');
                key = read.substr(0, i);
                value = read.substr(i + 1);

                converter << value;
                if (key == "id") {
                    converter >> charID;
                } else if (key == "x") {
                    converter >> chard.srcX;
                } else if (key == "y") {
                    converter >> chard.srcY;
                } else if (key == "width") {
                    converter >> chard.srcW;
                } else if (key == "height") {
                    converter >> chard.srcH;
                } else if (key == "xoffset") {
                    converter >> chard.xOff;
                } else if (key == "yoffset") {
                    converter >> chard.yOff;
                } else if (key == "xadvance") {
                    converter >> chard.xAdv;
                }
            }
            _chars.insert(std::pair<int, CharDesc>(charID, chard));
        }
    }

    fin.close();

    return true;
}

void BitmapFont::BuildVertexArray(VertexFont* vertex, int numvert, const wchar_t* sentence) {
    int numLetters = (int) wcslen(sentence);
    // следим чтобы число букв не было больше числа вершин
    if (numLetters * 4 > numvert) {
        numLetters = numvert / 4;
    }

    float drawX = (float) _render->_width / 2 * -1;
    float drawY = (float) _render->_height / 2;

    int index = 0;
    for (int i = 0; i < numLetters; i++) {
        float CharX = _chars[sentence[i]].srcX;
        float CharY = _chars[sentence[i]].srcY;
        float Width = _chars[sentence[i]].srcW;
        float Height = _chars[sentence[i]].srcH;
        float OffsetX = _chars[sentence[i]].xOff;
        float OffsetY = _chars[sentence[i]].yOff;

        float left = drawX + OffsetX;
        float right = left + Width;
        float top = drawY - OffsetY;
        float bottom = top - Height;
        float lefttex = CharX / _widthTex;
        float righttex = (CharX + Width) / _widthTex;
        float toptex = CharY / _heightTex;
        float bottomtex = (CharY + Height) / _heightTex;

        vertex[index].pos = XMFLOAT3(left, top, 0.0f);
        vertex[index].tex = XMFLOAT2(lefttex, toptex);
        index++;
        vertex[index].pos = XMFLOAT3(right, bottom, 0.0f);
        vertex[index].tex = XMFLOAT2(righttex, bottomtex);
        index++;
        vertex[index].pos = XMFLOAT3(left, bottom, 0.0f);
        vertex[index].tex = XMFLOAT2(lefttex, bottomtex);
        index++;
        vertex[index].pos = XMFLOAT3(right, top, 0.0f);
        vertex[index].tex = XMFLOAT2(righttex, toptex);
        index++;

        drawX += _chars[sentence[i]].xAdv;
    }
}

void BitmapFont::Draw(unsigned int index, float r, float g, float b, float x, float y)
{
    SetShaderParameters(r, g, b, x, y);

    _shader->Draw();
    _render->_pImmediateContext->DrawIndexed(index, 0, 0);
}

void BitmapFont::SetShaderParameters(float r, float g, float b, float x, float y) {
    XMMATRIX objmatrix = XMMatrixTranslation(x, -y, 0);
    XMMATRIX wvp = objmatrix * _render->_ortho;
    ConstantBuffer cb{};
    cb.WVP = XMMatrixTranspose(wvp);
    _render->_pImmediateContext->UpdateSubresource(_constantBuffer, 0, NULL, &cb, 0, 0);
    _render->_pImmediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);

    PixelBufferType pb{};
    pb.pixelColor = XMFLOAT4(r, g, b, 1.0f);
    _render->_pImmediateContext->UpdateSubresource(_pixelBuffer, 0, NULL, &pb, 0, 0);
    _render->_pImmediateContext->PSSetConstantBuffers(0, 1, &_pixelBuffer);
}

void BitmapFont::Close() {
    _RELEASE(_constantBuffer);
    _RELEASE(_pixelBuffer);
    _CLOSE(_shader);
}
