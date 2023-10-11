using ReactiveUI;
using ReactiveUI.Fody.Helpers;

namespace ImeSense.ShaderPlayground.ViewModels;

public class MainViewModel : ReactiveObject {
    /// <summary>
    /// Высота окна
    /// </summary>
    [Reactive]
    public int WindowWidth { get; set; } = 1280;

    /// <summary>
    /// Ширина окна
    /// </summary>
    [Reactive]
    public int WindowHeight { get; set; } = 720;

    /// <summary>
    /// Название окна
    /// </summary>
    [Reactive]
    public string? TitleName { get; set; } = "Shader Playground";

    /// <summary>
    /// Вкладка "Файл"
    /// </summary>
    [Reactive]
    public string? File { get; set; } = "Файл";

    /// <summary>
    /// Вкладка "Инструменты"
    /// </summary>
    [Reactive]
    public string? Tools { get; set; } = "Инструменты";

    /// <summary>
    /// Вкладка "Настройки"
    /// </summary>
    [Reactive]
    public string? Settings { get; set; } = "Настройки";

    /// <summary>
    /// Вкладка "Помощь"
    /// </summary>
    [Reactive]
    public string? Help { get; set; } = "Помощь";
}
