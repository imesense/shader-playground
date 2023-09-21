using System;

using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;

using ImeSense.ShaderPlayground.ViewModels;
using ImeSense.ShaderPlayground.Views;

using Microsoft.Extensions.DependencyInjection;

namespace ImeSense.ShaderPlayground;

public partial class App : Application {
    private readonly IServiceProvider _serviceProvider = null!;

    private static IServiceCollection ConfigureServices() {
        var services = new ServiceCollection();

        services.AddSingleton<MainViewModel>();
        services.AddSingleton<MainWindow>();

        return services;
    }

    public App() =>
        _serviceProvider = ConfigureServices().BuildServiceProvider();

    public override void Initialize() =>
        AvaloniaXamlLoader.Load(this);

    public override void OnFrameworkInitializationCompleted() {
        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop) {
            desktop.MainWindow = _serviceProvider
                .GetRequiredService<MainWindow>();
            desktop.MainWindow.DataContext = _serviceProvider
                .GetRequiredService<MainViewModel>();
        }

        base.OnFrameworkInitializationCompleted();
    }
}
