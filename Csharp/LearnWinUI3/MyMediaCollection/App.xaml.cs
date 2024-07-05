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
using MyMediaCollection.Helpers;
using MyMediaCollection.Interfaces;
using MyMediaCollection.Services;
using MyMediaCollection.ViewModels;
using MyMediaCollection.Views;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Security.EnterpriseData;
using Microsoft.Windows.AppLifecycle;
using Microsoft.Windows.AppNotifications;
using WinRT.Interop;

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
        internal Window Window => m_window;
        private static Window m_window;
        private NotificationManager notificationManager;

        [DllImport("user32.dll", SetLastError = true)]
        static extern void SwitchToThisWindow(IntPtr hWnd, bool turnOn);


        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            notificationManager = new();
            notificationManager.Init();
            AppDomain.CurrentDomain.ProcessExit += CurrentDomain_ProcessExit;
        }

        public static void ToForeground()
        {
            if (m_window != null)
            {
                IntPtr handle = WindowNative.GetWindowHandle(m_window);
                if (handle != IntPtr.Zero)
                {
                    SwitchToThisWindow(handle, true);
                }
            }
        }

        public static string GetFullPathToExe()
        {
            var path = AppDomain.CurrentDomain.BaseDirectory;
            var pos = path.LastIndexOf('\\');
            return path.Substring(0, pos);
        }

        public static string GetFullPathToAsset(string assetName)
        {
            return $"{GetFullPathToExe()}\\Assets\\{assetName}";
        }

        private void CurrentDomain_ProcessExit(object sender, EventArgs e)
        {
            notificationManager.Unregister();
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

            var currentInstance = Microsoft.Windows.AppLifecycle.AppInstance.GetCurrent();
            if (currentInstance.IsCurrent)
            {
                AppActivationArguments activationArguments = currentInstance.GetActivatedEventArgs();
                if (activationArguments != null)
                {
                    ExtendedActivationKind kind = activationArguments.Kind;
                    if (kind == ExtendedActivationKind.AppNotification)
                    {
                        AppNotificationActivatedEventArgs notificationActivatedEventArgs =
                            (AppNotificationActivatedEventArgs)activationArguments.Data;
                        notificationManager.ProcessLaunchActivationArgs(notificationActivatedEventArgs);
                    }
                }
            }

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
    }
}
