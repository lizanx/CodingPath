using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace GetStartedApp;

public partial class BindToControlWindowViewModel : ObservableObject
{
    [ObservableProperty] private string _counterText = "No count yet";
    private int _counter;

    [RelayCommand]
    private void AddCounter()
    {
        _counter++;
        CounterText = $"Counter: {_counter}";
    }
}