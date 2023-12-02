#pragma once

#include "Common/macros.h"

#include <clocale>
#include <ctime>

#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>

#define _XM_NO_INTRINSICS_
#include <DirectXMath.h>

#define WIN32_LEAN_AND_MEAN // Excludes rarely used libraries in Windows.h

#include <Windows.h>     // All of the Win32 stuff.
#include <d3d11_1.h>     // Direct3D library
#include <dxgi.h>        // DirectX Graphics Infrastructure 
#include <d3dcompiler.h> // Shader compiler

#include <DirectXMath.h> // SIMD math library utilizing SSE
using namespace DirectX;

#include "D3DX11tex.h"

#include <mmsystem.h>

#include <GL/gl.h>
#include "GL/glext.h"
#include "GL/wglext.h"
