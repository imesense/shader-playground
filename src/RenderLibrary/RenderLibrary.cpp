#include "StdAfx.h"

#include "framework.h"
#include "RenderLibrary.h"

// This is an example of an exported variable
RENDERLIBRARY_API int nRenderLibrary=0;

// This is an example of an exported function.
RENDERLIBRARY_API int fnRenderLibrary() {
    return 0;
}

// This is the constructor of a class that has been exported.
CRenderLibrary::CRenderLibrary() {
    return;
}
