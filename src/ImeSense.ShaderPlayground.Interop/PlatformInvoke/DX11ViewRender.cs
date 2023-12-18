using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

internal class DX11ViewRender {
    [DllImport("RenderLibrary", EntryPoint = "CreateRenderInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr Create();

    [DllImport("RenderLibrary", EntryPoint = "DestroyRenderInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Destroy(IntPtr instance);
}
