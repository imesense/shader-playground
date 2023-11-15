#pragma once

inline wchar_t* CharToWChar(char *mbString)
{ 
	//int len = 0; 
	//len = (int)strlen(mbString) + 1; 
	//wchar_t *ucString = new wchar_t[len]; 
	//mbstowcs_s(ucString, mbString, len);
	//return ucString; 

	int len = 0;
	len = (int)strlen(mbString) + 1;
	wchar_t* ucString = new wchar_t[len];

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, ucString, len, mbString, len - 1);

	return ucString;
}

inline std::wstring intToStr(int i)
{
	wchar_t str[255];
	swprintf_s(str, 255, L"%d", i);
	return str; 
}