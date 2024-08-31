using System;
using System.IO;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;
using Avalonia.Platform.Storage;

namespace GetStartedApp;

public partial class FilePickerWindow : Window
{
    public FilePickerWindow()
    {
        InitializeComponent();
    }

    private async void SaveButton_OnClick(object? sender, RoutedEventArgs e)
    {
        var topLevel = TopLevel.GetTopLevel(this)!;
        var file = await topLevel.StorageProvider.SaveFilePickerAsync(new FilePickerSaveOptions()
        {
            Title = "Save input text to file",
        });
        if (file is null) return;
        await using var stream = await file.OpenWriteAsync();
        using var writer = new StreamWriter(stream);
        await writer.WriteAsync((DataContext as FilePickerWindowViewModel)?.UserInputString ?? "Failed to get input string.");
        // await writer.WriteAsync("Hello Avalonia!");
    }

    private async void LoadButton_OnClick(object? sender, RoutedEventArgs e)
    {
        var topLevel = TopLevel.GetTopLevel(this)!;
        var files = await topLevel.StorageProvider.OpenFilePickerAsync(new FilePickerOpenOptions()
        {
            Title = "Load input text from file",
            AllowMultiple = false
        });
        if (files.Count != 1) throw new ArgumentException($"Invalid files count: {files.Count}");
        var vm = (DataContext as FilePickerWindowViewModel)!;
        await using var stream = await files[0].OpenReadAsync();
        using var reader = new StreamReader(stream);
        vm.FileContentString = await reader.ReadToEndAsync();
    }
}