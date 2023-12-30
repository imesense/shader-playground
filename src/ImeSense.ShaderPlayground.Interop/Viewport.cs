using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

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
            _nativeWindowHandle = Framework.CreateFabricDirectXWindow();

            string currentDirectory1 = AppDomain.CurrentDomain.BaseDirectory;
            string currentDirectory2 = System.IO.Directory.GetCurrentDirectory();

            Console.WriteLine("AppDomain.CurrentDomain.BaseDirectory: " + currentDirectory1);
            Console.WriteLine("System.IO.Directory.GetCurrentDirectory(): " + currentDirectory2);

            if (_nativeWindowHandle != IntPtr.Zero) {
                Task.Run(() => RunRender());
            } else { 
                Debug.Assert(_nativeWindowHandle != IntPtr.Zero); 
            }

            return new PlatformHandle(_nativeWindowHandle, "DirectX11");
        }

        return base.CreateNativeControlCore(parent);
    }

    protected override void DestroyNativeControlCore(IPlatformHandle control) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)) {
            Framework.DestroyWindow(_nativeWindowHandle);
            Framework.DestroyFabricDirectXWindow();
            _nativeWindowHandle = IntPtr.Zero;
        }

        base.DestroyNativeControlCore(control);
    }

    private async void RunRender() {
        while (true) {
            await Task.Delay(16); // 60 FPS
        }
    }
}
