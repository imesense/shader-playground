using System.Reactive;

using ReactiveUI;
using ReactiveUI.Fody.Helpers;

namespace ImeSense.ShaderPlayground.ViewModels;

public class MainViewModel : ReactiveObject {
    private readonly MenuViewModel _menuViewModel;

    public MainViewModel(MenuViewModel menuViewModel) {
        _menuViewModel = menuViewModel;

        MenuContext = _menuViewModel;

        PlayCommand = ReactiveCommand.Create(() => {
        });
        StopCommand = ReactiveCommand.Create(() => {
        });
        SettingsCommand = ReactiveCommand.Create(() => {
        });
    }

#if DEBUG
    public MainViewModel() {
        _menuViewModel = null!;

        MenuContext = null!;
        PlayCommand = null!;
        StopCommand = null!;
        SettingsCommand = null!;
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
    public int WindowWidth { get; set; } = 900;

    /// <summary>
    /// Название окна
    /// </summary>
    [Reactive]
    public string WindowTitle { get; set; } = "Shader Playground";

    [Reactive]
    public ReactiveObject MenuContext { get; init; }

    [Reactive]
    public string Resolution { get; set; } = "800x600";

    [Reactive]
    public string Frame { get; set; } = "60";

    public ReactiveCommand<Unit, Unit> PlayCommand { get; private set; }
    public ReactiveCommand<Unit, Unit> StopCommand { get; private set; }
    public ReactiveCommand<Unit, Unit> SettingsCommand { get; private set; }
}
