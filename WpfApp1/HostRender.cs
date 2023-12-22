using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace HostRender 
    {
    public class HostRender : HwndHost {
        private IntPtr windowHandle;

        public HostRender() {
            windowHandle = IntPtr.Zero;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent) {
            //windowHandle = RenderAPI.InitializeFramework(_framework, hwndParent.Handle, 800, 400);
            windowHandle = RenderAPI.InitializeWin32(hwndParent.Handle);
            return new HandleRef(this, windowHandle);
        }

        protected override void DestroyWindowCore(HandleRef hwnd) {
            windowHandle = IntPtr.Zero;
        }
    }
}
