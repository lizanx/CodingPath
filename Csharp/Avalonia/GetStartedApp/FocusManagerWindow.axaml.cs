using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;

namespace GetStartedApp;

public partial class FocusManagerWindow : Window
{
    public FocusManagerWindow()
    {
        InitializeComponent();
    }

    private void Focus_OnClick(object? sender, RoutedEventArgs e)
    {
        if (TopLevel.GetTopLevel(this) is not { } topLevel) return;
        
        var focusedElement = topLevel.FocusManager?.GetFocusedElement();
        if (focusedElement != InputTextBox)
        {
            InputTextBox.Focus();
        }
    }

    private void Focus2_OnClick(object? sender, RoutedEventArgs e)
    {
        InputTextBox.Focus();
    }

    private void ClearFocus_OnClick(object? sender, RoutedEventArgs e)
    {
        if (TopLevel.GetTopLevel(this) is not { } topLevel) return;
        
        topLevel.FocusManager?.ClearFocus();
    }
}