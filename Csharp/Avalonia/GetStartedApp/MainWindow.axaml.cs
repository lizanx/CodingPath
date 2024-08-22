using System.Diagnostics;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;

namespace GetStartedApp;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        celsius.AddHandler(TextInputEvent, Celsius_TextInput, RoutingStrategies.Tunnel);
    }

    public void Button_Clicked(object sender, RoutedEventArgs e)
    {
        if (double.TryParse(celsius.Text, out double C))
        {
            fahrenheit.Text = (C * 9 / 5 + 32).ToString("0.0");
        }
        else
        {
            celsius.Text = "0";
            fahrenheit.Text = "0";
        }

        Debug.WriteLine($"Click: Celsius = {celsius.Text}, Fahrenheit = {fahrenheit.Text}");
    }

    public void Celsius_TextInput(object? sender, TextInputEventArgs args)
    {
        Debug.WriteLine(
            $"Celsius_TextInput triggered, input: {args.Text}, celsius.Text: {celsius.Text}"
        );
        // When the routed input event is being handled, the actual value of "celsius.Text" hasn't been updated.
        // Thus, the value of "celsius.Text" is always one letter less than the real input.
        // Below we use "celsius.Text + args.Text" to get the complete input.
        if (double.TryParse(celsius.Text + args.Text, out double C))
        {
            fahrenheit.Text = (C * 9 / 5 + 32).ToString("0.0");
        }
        else
        {
            Debug.WriteLine($"Failed to convert to double from {celsius.Text}");
        }
    }
}
