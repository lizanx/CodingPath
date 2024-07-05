using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using MyMediaCollection.ViewModels;
using Microsoft.Extensions.DependencyInjection;
using MyMediaCollection.Helpers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace MyMediaCollection.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainViewModel ViewModel;
        public static MainPage Current;

        public MainPage()
        {
            ViewModel = App.HostContainer.Services.GetRequiredService<MainViewModel>();
            this.InitializeComponent();
            Current = this;
            Loaded += MainPage_Loaded;
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            var mainWindow = (Application.Current as App)?.Window as MainWindow;
            if (mainWindow != null)
            {
                mainWindow.SetPageTitle("Home");
            }
        }

        public void NotifyUser(string message, InfoBarSeverity severity, bool isOpen = true)
        {
            if (DispatcherQueue.HasThreadAccess)
            {
                UpdateStatus(message, severity, isOpen);
            }
            else
            {
                DispatcherQueue.TryEnqueue(() =>
                    UpdateStatus(message, severity, isOpen));
            }
        }

        private void UpdateStatus(string message, InfoBarSeverity severity, bool isOpen)
        {
            notifyInfoBar.Message = message;
            notifyInfoBar.Severity = severity;
            notifyInfoBar.IsOpen = isOpen;
        }

        public void NotificationReceived(NotificationShared.Notification notification)
        {
            string text = $"{notification.Originator}; Action: {notification.Action}";

            if (notification.HasInput)
            {
                if (string.IsNullOrWhiteSpace(notification.Input))
                {
                    text += "; No input received";
                }
                else
                {
                    text += $"; Input received: {notification.Input}";
                }
            }

            if (DispatcherQueue.HasThreadAccess)
            {
                DisplayMessageDialog(text);
            }
            else
            {
                DispatcherQueue.TryEnqueue(() =>
                    DisplayMessageDialog(text));
            }
        }

        private void DisplayMessageDialog(string  message)
        {
            ContentDialog contentDialog = new()
            {
                XamlRoot = this.XamlRoot,
                Title = "Notification Received",
                Content = message,
                CloseButtonText = "OK"
            };
            contentDialog.ShowAsync();
        }
    }
}
