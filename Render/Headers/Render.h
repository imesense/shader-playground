#pragma once

#include "..\resource.h"

#define WIN32_LEAN_AND_MEAN // Excludes rarely used libraries in Windows.h

#include <Windows.h>     // All of the Win32 stuff.
#include <d3d11_1.h>     // Direct3D library
//#include <d3d10.h>		// Direct3D library
#include <dxgi.h>        // DirectX Graphics Infrastructure 
#include <d3dcompiler.h> // Shader compiler
#include <DirectXMath.h> // SIMD math library utilizing SSE