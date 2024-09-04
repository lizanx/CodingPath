using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using ReactiveApp.ViewModels;
using ReactiveApp.Views;

namespace ReactiveApp;

public partial class App : Application
{
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);
    }

    public override void OnFrameworkInitializationCompleted()
    {
        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            // desktop.MainWindow = new MainWindow
            // {
            //     DataContext = new MainWindowViewModel(),
            // };

            desktop.MainWindow = new CanExecuteWindow()
            {
                DataContext = new CanExecuteWindowViewModel()
            };
        }

        base.OnFrameworkInitializationCompleted();
    }
}