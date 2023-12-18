namespace ImeSense.ShaderPlayground.Interop.PlatformInvoke;

public class DescWindow {
    public string caption;
    public int width;
    public int height;
    public int posx;
    public int posy;
    public bool resizing;

    public DescWindow() {
        caption = string.Empty;
        width = 640;
        height = 480;
        posx = 200;
        posy = 20;
        resizing = true;
    }
}
