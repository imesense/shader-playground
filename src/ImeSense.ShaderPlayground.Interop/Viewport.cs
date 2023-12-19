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
            _framework = Framework.Create();

            IntPtr render = DX11ViewRender.Create();
            IntPtr input = InputBinder.Create(render);

            FrameworkDesc desc = new() {
                render = render
            };

            Framework.Initialize(_framework, desc);
            Framework.AddInputListener(_framework, input);
            Framework.Run(_framework);

            return new PlatformHandle(_framework, "Framework");
        }

        return base.CreateNativeControlCore(parent);
    }

    protected override void DestroyNativeControlCore(IPlatformHandle control) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            Framework.Close(_framework);
            return;
        }

        base.DestroyNativeControlCore(control);
    }
}
