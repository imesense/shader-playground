using ReactiveUI;
using ReactiveUI.Fody.Helpers;

namespace ImeSense.ShaderPlayground.ViewModels;

public class MenuViewModel : ReactiveObject {
    /// <summary>
    /// Меню файл
    /// </summary>
    [Reactive]
    public string FileHeader { get; set; } = "Файл";

    /// <summary>
    /// Меню инструменты
    /// </summary>
    [Reactive]
    public string ToolsHeader { get; set; } = "Инструменты";

    /// <summary>
    /// Меню настройки
    /// </summary>
    [Reactive]
    public string SettingsHeader { get; set; } = "Настройки";

    /// <summary>
    /// Меню помощь
    /// </summary>
    [Reactive]
    public string HelpHeader { get; set; } = "Помощь";
}
