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
