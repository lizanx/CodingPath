using Avalonia;
using Avalonia.Controls;
using Avalonia.Input.Platform;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;

namespace ReactiveApp.Views;

public partial class ClipboardWindow : Window
{
    public ClipboardWindow()
    {
        InitializeComponent();
    }

    private async void ShowClipboard(object? sender, RoutedEventArgs e)
    {
        var toplevel = TopLevel.GetTopLevel(this);
        string clipboardText;
        if (toplevel?.Clipboard is { } clipboard)
        {
            clipboardText = await clipboard.GetTextAsync() ?? "No text in clipboard";
        }
        else
        {
            clipboardText = "Failed to get text from clipboard.";
        }
        
        ClipboardTextBlock.Text = clipboardText;
    }
}