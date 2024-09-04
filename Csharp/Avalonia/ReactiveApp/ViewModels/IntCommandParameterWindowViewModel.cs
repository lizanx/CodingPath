using System.Reactive;
using ReactiveUI;

namespace ReactiveApp.ViewModels;

public class IntCommandParameterWindowViewModel : ReactiveObject
{
    private int _passedInValue;

    public int PassedInValue
    {
        get => _passedInValue;
        set => this.RaiseAndSetIfChanged(ref _passedInValue, value);
    }
    
    public ReactiveCommand<int, Unit> ShowIntCommand { get; }
    
    public IntCommandParameterWindowViewModel()
    {
        ShowIntCommand = ReactiveCommand.Create<int>(ShowInt);
    }

    private void ShowInt(int passedInValue)
    {
        PassedInValue = passedInValue;
    }
}