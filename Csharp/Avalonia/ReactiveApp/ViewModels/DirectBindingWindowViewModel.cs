using System;

namespace ReactiveApp.ViewModels;

public class DirectBindingWindowViewModel
{
    // Avalonia allows direct Command-to-Function bindings for simple use cases.
    // But for complex apps, it's better to use ICommand interface to separate concerns.
    public void DebugPrintMessage(object msg)
    {
        Console.WriteLine(msg);
    }

    public bool CanDebugPrintMessage(object msg) =>
        msg is string s && !string.IsNullOrWhiteSpace(s);
}
