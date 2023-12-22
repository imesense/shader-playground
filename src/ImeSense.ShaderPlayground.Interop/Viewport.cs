using System;
using System.Runtime.InteropServices;

using Avalonia.Controls;
using Avalonia.Platform;

using ImeSense.ShaderPlayground.Interop.PlatformInvoke;

namespace ImeSense.ShaderPlayground.Interop;

public class Viewport : NativeControlHost {
    private IntPtr _framework;

    protected override IPlatformHandle CreateNativeControlCore(IPlatformHandle parent) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            //_framework = Framework.Create();

            //Framework.Initialize(_framework);
            //Framework.Run(_framework);

            _framework = Framework.InitializeWin32(parent.Handle);

            return new PlatformHandle(_framework, "DX11Window");
        }

        return base.CreateNativeControlCore(parent);
    }

    protected override void DestroyNativeControlCore(IPlatformHandle control) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            //Framework.Close(_framework);
            return;
        }

        base.DestroyNativeControlCore(control);
    }
}
