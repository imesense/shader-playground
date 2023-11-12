#pragma once

namespace Constants
{
	typedef struct
	{
		bool USE_DX10;
		bool USE_DX11;

		bool USE_OPEN_GL;

	} IntConstantsArray;

	class Constants
	{
		void Init(bool Init = true);
	};
}

extern Constants::IntConstantsArray* pIntConstantsArray;