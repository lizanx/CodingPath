using System.Text;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Markup.Xaml;

namespace GetStartedApp;

public partial class PointerEventWindow : Window
{
    public PointerEventWindow()
    {
        InitializeComponent();
    }

    private void PointerPressedHandler(object? sender, PointerPressedEventArgs args)
    {
        var point = args.GetCurrentPoint(sender as Control);
        var sb = new StringBuilder();
        if (point.Properties.IsLeftButtonPressed)
        {
            sb.AppendLine("LeftButton pressed");
        }
        else if (point.Properties.IsRightButtonPressed)
        {
            sb.AppendLine("RightButton pressed");
        }

        sb.AppendLine($"Pointer pressed at [{point.Position.X}, {point.Position.Y}]");
        
        InfoText.Text = sb.ToString();
    }
}