using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;

namespace GetStartedApp;

public partial class InteractivityWindow : Window
{
    private int _clickCount = 0;
    
    public InteractivityWindow()
    {
        InitializeComponent();
    }

    private void Button_OnClick(object? sender, RoutedEventArgs e)
    {
        _clickCount++;
        ClickCountText.Text = $"You've clicked the button {_clickCount} times!";
    }
}