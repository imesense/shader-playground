// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RENDERLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RENDERLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RENDERLIBRARY_EXPORTS
#define RENDERLIBRARY_API __declspec(dllexport)
#else
#define RENDERLIBRARY_API __declspec(dllimport)
#endif

// This class is exported from the dll
class RENDERLIBRARY_API CRenderLibrary {
public:
	CRenderLibrary(void);
	// TODO: add your methods here.
};

extern RENDERLIBRARY_API int nRenderLibrary;

RENDERLIBRARY_API int fnRenderLibrary(void);
