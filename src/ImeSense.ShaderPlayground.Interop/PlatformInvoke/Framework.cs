using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

internal class Framework {
    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool DestroyWindow(IntPtr hWnd);

    [DllImport("RenderLibrary", EntryPoint = "CreateFabricDirectXWindow", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateFabricDirectXWindow();

    [DllImport("RenderLibrary", EntryPoint = "DestroyFabricDirectXWindow", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyFabricDirectXWindow();

    [DllImport("RenderLibrary", EntryPoint = "Frame", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool Frame();

    [DllImport("RenderLibrary", EntryPoint = "MessageLoop", CallingConvention = CallingConvention.Cdecl)]
    public static extern void MessageLoop(IntPtr hWnd);

    [DllImport("RenderLibrary", EntryPoint = "CreateScene", CallingConvention = CallingConvention.Cdecl)]
    public static extern void CreateScene(IntPtr hWnd);
}
