using ReactiveUI;
using ReactiveUI.Fody.Helpers;

namespace ImeSense.ShaderPlayground.ViewModels;

public class MainViewModel : ReactiveObject {
    private readonly MenuViewModel _menuViewModel;

    public MainViewModel(MenuViewModel menuViewModel) {
        _menuViewModel = menuViewModel;

        MenuContext = _menuViewModel;
    }

#if DEBUG
    public MainViewModel() {
        _menuViewModel = null!;

        MenuContext = null!;
    }
#endif

    /// <summary>
    /// Ширина окна
    /// </summary>
    [Reactive]
    public int WindowHeight { get; set; } = 600;

    /// <summary>
    /// Высота окна
    /// </summary>
    [Reactive]
    public int WindowWidth { get; set; } = 800;

    /// <summary>
    /// Название окна
    /// </summary>
    [Reactive]
    public string WindowTitle { get; set; } = "Shader Playground";

    [Reactive]
    public ReactiveObject MenuContext { get; init; }
}
