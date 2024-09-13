using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using ReactiveApp.ViewModels;
using ReactiveUI;

namespace ReactiveApp.Views;

public partial class DataPersistenceWindow : ReactiveWindow<DataPersistenceWindowViewModel>
{
    public DataPersistenceWindow()
    {
        AvaloniaXamlLoader.Load(this);
        this.WhenActivated(disposable => { });
    }
}