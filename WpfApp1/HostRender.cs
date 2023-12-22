using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace HostRender 
{
    /*
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
    */
    public class HostRender : HwndHost {
        private IntPtr windowHandle;
        private bool rendering = true; // Флаг для управления бесконечным циклом

        public HostRender() {
            windowHandle = IntPtr.Zero;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent) {
            //windowHandle = RenderAPI.InitializeFramework(_framework, hwndParent.Handle, 800, 400);
            windowHandle = RenderAPI.InitializeWin32(hwndParent.Handle);

            // Запуск потока для бесконечного цикла обновления
            Task.Run(() => RenderLoop());

            return new HandleRef(this, windowHandle);
        }

        protected override void DestroyWindowCore(HandleRef hwnd) {
            rendering = false; // Остановка бесконечного цикла
            windowHandle = IntPtr.Zero;
        }

        private void RenderLoop() {
            // Ваш бесконечный цикл обновления
            while (rendering) {
                // Обновление рендера здесь
                // Например: RenderAPI.Update();
                Debug.WriteLine("1111111111111");
                RenderAPI.Frame();
                // Можно добавить задержку, чтобы управлять частотой обновления
                Thread.Sleep(16); // 16 миллисекунд для приближенной к 60 FPS частоте обновления
            }
        }
    }
}
