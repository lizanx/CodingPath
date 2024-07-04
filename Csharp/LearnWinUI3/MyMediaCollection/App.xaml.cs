using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Microsoft.UI.Xaml.Shapes;
using MyMediaCollection.Interfaces;
using MyMediaCollection.Services;
using MyMediaCollection.ViewModels;
using MyMediaCollection.Views;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Security.EnterpriseData;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace MyMediaCollection
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        //public static MainViewModel ViewModel { get; } = new MainViewModel();
        public static IHost HostContainer { get; private set; }

        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// Invoked when the application is launched.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        protected override async void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
        {
            m_window = new MainWindow();
            var rootFrame = new Frame();
            await RegisterComponentsAsync(rootFrame);
            rootFrame.NavigationFailed += RootFrame_NavigationFailed;
            rootFrame.Navigate(typeof(MainPage), args);
            m_window.Content = rootFrame;
            m_window.Activate();
        }

        private void RootFrame_NavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception($"Error loading page {e.SourcePageType.FullName}");
        }

        private async Task RegisterComponentsAsync(Frame rootFrame)
        {
            var navigationService = new NavigationService(rootFrame);
            navigationService.Configure(nameof(MainPage), typeof(MainPage));
            navigationService.Configure(nameof(ItemDetailsPage), typeof(ItemDetailsPage));

            var dataService = new SqliteDataService();
            await dataService.InitializeDataAsync();

            HostContainer = Host.CreateDefaultBuilder()
                .ConfigureServices(services =>
                {
                    services.AddSingleton<INavigationService>(navigationService);
                    services.AddSingleton<IDataService>(dataService);
                    services.AddTransient<MainViewModel>();
                    services.AddTransient<ItemDetailsViewModel>();
                })
                .Build();
        }

        private Window m_window;
    }
}
