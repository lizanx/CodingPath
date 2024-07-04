using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using MyMediaCollection.Model;
using MyMediaCollection.Enums;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using MyMediaCollection.ViewModels;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.UI.Windowing;
using WinRT.Interop;
using Microsoft.UI;
using Microsoft.UI.Composition.SystemBackdrops;
using WinRT;
using Microsoft.UI.Composition;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace MyMediaCollection
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        private AppWindow _appWindow;
        private const string AppTitle = "My Media Collection";
        private DesktopAcrylicController desktopAcrylicController;

        public MainWindow()
        {
            this.InitializeComponent();

            //SystemBackdrop = new DesktopAcrylicBackdrop();

            _appWindow = GetCurrentAppWindow();
            _appWindow.Title = AppTitle;
        }

        private AppWindow GetCurrentAppWindow()
        {
            IntPtr handle = WindowNative.GetWindowHandle(this);
            WindowId windowId = Win32Interop.GetWindowIdFromWindow(handle);
            return AppWindow.GetFromWindowId(windowId);
        }

        internal void SetPageTitle(string title)
        {
            if (_appWindow == null)
            {
                _appWindow = GetCurrentAppWindow();
            }

            _appWindow.Title = $"{AppTitle} - {title}";
        }
    }
}
