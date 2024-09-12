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
            // desktop.MainWindow = new BindingToTaskWindow()
            // {
            //     DataContext = new BindingToTaskWindowViewModel()
            // };

            // desktop.MainWindow = new DirectBindingWindow()
            // {
            //     DataContext = new DirectBindingWindowViewModel()
            // };
            //
            // desktop.MainWindow = new IntCommandParameterWindow()
            // {
            //     DataContext = new IntCommandParameterWindowViewModel()
            // };
            //
            desktop.MainWindow = new CanExecuteWindow()
            {
                DataContext = new CanExecuteWindowViewModel()
            };

            // desktop.MainWindow = new MainWindow
            // {
            //     DataContext = new MainWindowViewModel(),
            // };
        }

        base.OnFrameworkInitializationCompleted();
    }
}