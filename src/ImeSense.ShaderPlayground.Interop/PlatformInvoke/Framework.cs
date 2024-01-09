using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

internal class Framework {
    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool DestroyWindow(IntPtr hWnd);

    [DllImport("C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary.dll", EntryPoint = "CreateFabricDirectXWindow", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateFabricDirectXWindow();

    [DllImport("C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary.dll", EntryPoint = "DestroyFabricDirectXWindow", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyFabricDirectXWindow();

    [DllImport("C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary.dll", EntryPoint = "Frame", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool Frame();

    [DllImport("C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary.dll", EntryPoint = "MessageLoop", CallingConvention = CallingConvention.Cdecl)]
    public static extern void MessageLoop(IntPtr hWnd);

    [DllImport("C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary.dll", EntryPoint = "CreateScene", CallingConvention = CallingConvention.Cdecl)]
    public static extern void CreateScene(IntPtr hWnd);
}
