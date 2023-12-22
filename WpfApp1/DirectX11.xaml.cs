using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace HostRender {
    /// <summary>
    /// Логика взаимодействия для DirectX11.xaml
    /// </summary>
    public partial class DirectX11 : UserControl
    {
        private enum Win32Msg {
            WM_SIZE = 0x0005,
            WM_SIZING = 0x0214,
            WM_ENTERSIZEMOVE = 0X0231,
            WM_EXITSIZEMOVE = 0x0232
        }

        private bool disposed;
        //private IntPtr _framework;
        private HostRender host = null!;

        public DirectX11()
        {
            InitializeComponent();

            //_framework = RenderAPI.Create();
            Loaded += DirectX11ViewLoaded;
            //RenderAPI.Initialize(_framework);
            //RenderAPI.Run(_framework);
        }

        private void DirectX11ViewLoaded(object sender, RoutedEventArgs e) {
            Loaded -= DirectX11ViewLoaded;
            host = new HostRender();
            //RenderAPI.Run(_framework);
            //Debug.Assert(windowHandle != IntPtr.Zero);
            host.MessageHook += new System.Windows.Interop.HwndSourceHook(HostMessageFilter);
            Content = host;
        }

        private IntPtr HostMessageFilter(IntPtr hwnd, int msg, IntPtr wparam, IntPtr lparam,
            ref bool handled) {
            switch ((Win32Msg) msg) {
                case Win32Msg.WM_SIZING: break;
                case Win32Msg.WM_ENTERSIZEMOVE: break;
                case Win32Msg.WM_EXITSIZEMOVE: break;
                case Win32Msg.WM_SIZE: break;
                default: break;
            }
            return IntPtr.Zero;
        }

        protected virtual void Dispose(bool disposing) {
            if (!disposed) {
                if (disposing)
                    host.Dispose();
                disposed = true;
            }
        }

        public void Dispose() {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }
}
