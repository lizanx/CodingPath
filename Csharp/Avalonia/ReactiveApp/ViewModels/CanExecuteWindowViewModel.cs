using System.Reactive;
using ReactiveUI;

namespace ReactiveApp.ViewModels;

public class CanExecuteWindowViewModel : ReactiveObject
{
    private string _message = string.Empty;
    private string _output = "Waiting...";

    public string Message
    {
        get => _message;
        set => this.RaiseAndSetIfChanged(ref _message, value);
    }

    public string Output
    {
        get => _output;
        set => this.RaiseAndSetIfChanged(ref _output, value);
    }
    
    public ReactiveCommand<Unit, Unit> ShowOutputCommand { get; }

    public CanExecuteWindowViewModel()
    {
        var isValidObservable = this.WhenAnyValue(x => x.Message, x => !string.IsNullOrWhiteSpace(x));
        ShowOutputCommand = ReactiveCommand.Create(ShowOutput, isValidObservable);
    }

    private void ShowOutput()
    {
        Output = $"Output: {Message}";
        Message = string.Empty;
    }

}