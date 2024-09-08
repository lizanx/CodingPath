using System;
using System.Threading.Tasks;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.Threading;

namespace GetStartedApp;

public partial class UIThreadWindow : Window
{
    public UIThreadWindow()
    {
        InitializeComponent();

        Task.Run(() => ChangeTextFromAnotherThread("This is the text set after initialization."));
    }
    
    private void SetText(string text) => TestTextBlock.Text = text;

    private string GetText() => TestTextBlock.Text ?? string.Empty;

    private async Task ChangeTextFromAnotherThread(string text)
    {
        try
        {
            await Task.Delay(3 * 1000);
            
            Dispatcher.UIThread.Post(() => SetText("Change text via UIThread.Post"));
            
            await Task.Delay(3 * 1000);

            var originalText = await Dispatcher.UIThread.InvokeAsync(GetText);
            var newText = originalText + Environment.NewLine + "This line is added after getting the original text.";
            await Dispatcher.UIThread.InvokeAsync(() => SetText(newText));

            // This will cause exception since the function is called from non-UI thread.
            // The exception won't break the app directly since it's on another thread,
            // but the printings below in catch block will testify that exceptions did happen.
            // SetText("Set text directly from another thread.");
        }
        catch (Exception e)
        {
            Console.WriteLine($"### Exception: {e.Message} ###");
            throw;
        }
    }
}