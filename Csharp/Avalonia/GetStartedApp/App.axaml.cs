using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Data.Core.Plugins;
using Avalonia.Markup.Xaml;
using GetStartedApp.Models;
using GetStartedApp.Services;
using Microsoft.Extensions.DependencyInjection;

namespace GetStartedApp;

public partial class App : Application
{
    public static ServiceProvider ServiceProvider { get; private set; } = default!;
    
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);
    }

    public override void OnFrameworkInitializationCompleted()
    {
        BindingPlugins.DataValidators.RemoveAt(0);
        
        var servicesCollection = new ServiceCollection();
        servicesCollection.AddSingleton<IDataAccessService<Employee>, LocalDataAccessService<Employee>>();
        servicesCollection.AddTransient<IEmployeeService, EmployeeService>();
        servicesCollection.AddTransient<DependencyInjectionWindowViewModel>();
        servicesCollection.AddTransient<PropertyChangedWindowViewModel>();
        servicesCollection.AddTransient<BindToControlWindowViewModel>();
        ServiceProvider = servicesCollection.BuildServiceProvider();
        
        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            // desktop.MainWindow = new MainWindow();
            // desktop.MainWindow = new CanvasWindow();
            // desktop.MainWindow = new DockPanelWindow();
            // desktop.MainWindow = new GridWindow();
            // desktop.MainWindow = new StackPanelWindow();
            // desktop.MainWindow = new WrapPanelWindow();
            // desktop.MainWindow = new UniformGridWindow();
            // desktop.MainWindow = new StyleThemeWindow();
            // desktop.MainWindow = new ThemeVariantWindow();
            // desktop.MainWindow = new InteractivityWindow()
            // {
            //     DataContext = new InteractivityWindowViewModel()
            // };
            // desktop.MainWindow = new ImageAssetWindow();
            // desktop.MainWindow = new FilePickerWindow()
            // {
            //     DataContext = new FilePickerWindowViewModel()
            // };
            // desktop.MainWindow = new CompileBindingWindow()
            // {
            //     DataContext = new CompileBindingWindowViewModel()
            // };
            desktop.MainWindow = new DataTemplateWindow()
            {
                DataContext = new DataTemplateWindowViewModel()
            };
            
            // var vm = ServiceProvider.GetRequiredService<DependencyInjectionWindowViewModel>();
            // desktop.MainWindow = new DependencyInjectionWindow
            // {
            //     DataContext = vm
            // };

            // var vm = ServiceProvider.GetRequiredService<PropertyChangedWindowViewModel>();
            // desktop.MainWindow = new PropertyChangedWindow()
            // {
            //     DataContext = vm
            // };
            
            // var vm = ServiceProvider.GetRequiredService<BindToControlWindowViewModel>();
            // desktop.MainWindow = new BindToControlWindow()
            // {
            //     DataContext = vm
            // };
        }

        base.OnFrameworkInitializationCompleted();
    }
}
