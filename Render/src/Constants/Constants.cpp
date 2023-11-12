#include "stdafx.h"
#include "Constants.h"

Constants::IntConstantsArray* pIntConstantsArray = nullptr;

namespace Constants
{
	void Constants::Init(bool Init)
	{
		pIntConstantsArray->USE_DX10 = false;
		pIntConstantsArray->USE_DX11 = false;

		pIntConstantsArray->USE_OPEN_GL = false;
	}
}