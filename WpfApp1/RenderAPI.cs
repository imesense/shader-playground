using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace HostRender {
    internal class RenderAPI 
    {
        const string DllPath = "C:\\Users\\User\\Documents\\GitHub\\shader-playground\\bin\\x64\\Debug\\RenderLibrary";
        public static void DisplayDllPath() => Debug.WriteLine($"DLL Path: {DllPath}");

        [DllImport(DllPath/*, EntryPoint = "InitializeFramework", CallingConvention = CallingConvention.Cdecl)*/)]
        public static extern IntPtr InitializeFramework(IntPtr instance);

        private const string windowDll = @"C:\Users\User\Documents\GitHub\shader-playground\bin\x64\Debug\RenderLibrary";

        [DllImport(windowDll)]
        public static extern IntPtr InitializeWin32(IntPtr host);

        [DllImport(windowDll)]
        public static extern IntPtr Frame();

        /// <summary>
        /// /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>
        /// <returns></returns>

        [DllImport(DllPath, EntryPoint = "CreateFrameworkInstance", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Create();

        [DllImport(DllPath, EntryPoint = "DestroyFrameworkInstance", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Destroy(IntPtr instance);

        //[DllImport(DllPath, EntryPoint = "InitializeFramework", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void Initialize(IntPtr instance);

        [DllImport(DllPath, EntryPoint = "RunFramework", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Run(IntPtr instance);

        [DllImport(DllPath, EntryPoint = "CloseFramework", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Close(IntPtr instance);
    }
}
