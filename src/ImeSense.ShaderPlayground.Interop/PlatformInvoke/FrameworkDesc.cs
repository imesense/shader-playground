using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

[StructLayout(LayoutKind.Sequential)]
public class FrameworkDesc {
    public DescWindow wnd = null!;
    public IntPtr render;
}
