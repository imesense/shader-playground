using System.Runtime.InteropServices;
using System;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

internal class InputBinder {
    [DllImport("RenderLibrary", EntryPoint = "CreateInputBinderInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr Create(IntPtr render);

    [DllImport("RenderLibrary", EntryPoint = "DestroyFrameworkInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Destroy(IntPtr instance);
}
