using System.IO;
using System.Reflection;

namespace ImeSense.ShaderPlayground;

internal class ResourceLoader {
    const string SampleFilesPrefix = "ImeSense.ShaderPlayground.Resources.";

    internal static string LoadSampleFile(string fileName) {
        Stream stream = typeof(ResourceLoader).GetTypeInfo().Assembly.GetManifestResourceStream(SampleFilesPrefix + fileName)!;

        if (stream == null)
            return string.Empty;

        using (stream)
        using (StreamReader reader = new(stream)) {
            return reader.ReadToEnd();
        }
    }
}
