using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

internal class Framework {
    [DllImport("RenderLibrary", EntryPoint = "CreateFrameworkInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr Create();

    [DllImport("RenderLibrary", EntryPoint = "DestroyFrameworkInstance", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Destroy(IntPtr instance);

    [DllImport("RenderLibrary", EntryPoint = "InitializeFramework", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Initialize(IntPtr instance);

    [DllImport("RenderLibrary", EntryPoint = "RunFramework", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Run(IntPtr instance);

    [DllImport("RenderLibrary", EntryPoint = "CloseFramework", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Close(IntPtr instance);

    [DllImport("RenderLibrary")]
    public static extern IntPtr InitializeWin32(IntPtr host);
}
