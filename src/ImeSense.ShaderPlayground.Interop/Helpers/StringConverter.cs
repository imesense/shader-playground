using System;
using System.Runtime.InteropServices;

namespace ImeSense.ShaderPlayground.Interop.Helpers;

public static class StringConverter {
    public static string ConvertToString(IntPtr wcharPtr) {
        return Marshal.PtrToStringUni(wcharPtr)!;
    }

    public static IntPtr ConvertToWString(string str) {
        str ??= string.Empty;

        char[] chars = str.ToCharArray();
        IntPtr wcharPtr = Marshal.AllocHGlobal(2 * (chars.Length + 1));

        Marshal.Copy(chars, 0, wcharPtr, chars.Length);
        Marshal.WriteInt16(wcharPtr, chars.Length * 2, 0);

        return wcharPtr;
    }
}
