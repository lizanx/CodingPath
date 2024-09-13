using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using ReactiveApp.ViewHelpers;
using ReactiveApp.ViewModels;
using ReactiveApp.Views;
using ReactiveUI;

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
            var suspension = new AutoSuspendHelper(ApplicationLifetime);
            RxApp.SuspensionHost.CreateNewAppState = () => new DataPersistenceWindowViewModel();
            RxApp.SuspensionHost.SetupDefaultSuspendResume(new JsonSuspensionDriver("appstate.json"));
            suspension.OnFrameworkInitializationCompleted();
            var state = RxApp.SuspensionHost.GetAppState<DataPersistenceWindowViewModel>();
            desktop.MainWindow = new DataPersistenceWindow()
            {
                DataContext = state
            };
            
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
            // desktop.MainWindow = new CanExecuteWindow()
            // {
            //     DataContext = new CanExecuteWindowViewModel()
            // };

            // desktop.MainWindow = new MainWindow
            // {
            //     DataContext = new MainWindowViewModel(),
            // };
        }

        base.OnFrameworkInitializationCompleted();
    }
}