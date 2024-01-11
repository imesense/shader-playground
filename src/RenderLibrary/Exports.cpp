#include "StdAfx.h"

#include <list>
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include "Memory.hpp"
#include "InputCodes.hpp"
#include "InputListener.hpp"
#include "InputBinder.hpp"
#include "RenderState.hpp"
#include <wrl/client.h>
#include "Render.hpp"
#include "Shader.hpp"
#include "DepthShader.hpp"
#include "RenderTarget.hpp"
#include "Light.hpp"
#include "ShadowShader.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "DX11ViewRender.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "FabricDirectXWindow.hpp"
#include "Exports.hpp"
#include "Helpers.hpp"
#include "BitmapFont.h"
#include "RenderText.hpp"

using namespace ShaderPlayground;
