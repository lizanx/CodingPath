using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace GetStartedApp;

public partial class PropertyChangedWindow : Window
{
    public PropertyChangedWindow()
    {
        InitializeComponent();

        ClickButton.Click += (sender, e) =>
        {
            if (DataContext is PropertyChangedWindowViewModel vm)
                vm.ClickCounter++;
        };
    }
}