using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

using Avalonia.Controls;
using Avalonia.Platform;

using ImeSense.ShaderPlayground.Interop.PlatformInvoke;

namespace ImeSense.ShaderPlayground.Interop;

public class Viewport : NativeControlHost {
    private IntPtr _nativeWindowHandle;

    public Viewport() {
        _nativeWindowHandle = IntPtr.Zero;
    }

    protected override IPlatformHandle CreateNativeControlCore(IPlatformHandle parent) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            _nativeWindowHandle = Framework.CreateNativeWindow();
            Debug.Assert(_nativeWindowHandle != IntPtr.Zero);
            return new PlatformHandle(_nativeWindowHandle, "WND");
        }

        return base.CreateNativeControlCore(parent);
    }

    protected override void DestroyNativeControlCore(IPlatformHandle control) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            Framework.DestroyWindow(_nativeWindowHandle);
            Framework.DestroyNativeWindow();
            _nativeWindowHandle = IntPtr.Zero;
        }

        base.DestroyNativeControlCore(control);
    }
}
