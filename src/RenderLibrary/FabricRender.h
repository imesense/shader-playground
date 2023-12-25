#pragma once

namespace ShaderPlayground
{
    enum ErrorDescription {
        E_OK = 805,
        E_CREATE_VIEW_RENDER = 806,
        E_INPUT_BINDER = 807,
        E_WINDOW = 807,
        E_INPUT_MANAGER = 808,
        E_CREATE_DEVICE = 809,
        E_SHADER_DEPTH_INIT = 810,
        E_SHADER_SHADOW_INIT = 811,
    };

    class RENDERLIBRARY_API CFabricRender {
    public:
        CFabricRender();
        virtual ~CFabricRender();

        int CreateFabricRender();

        void DestroyFabricRender();
        bool RunRender();

        static bool bFabricInit;
    };

    //extern RENDERLIBRARY_API CFabricRender* pCFabricRender;
}
