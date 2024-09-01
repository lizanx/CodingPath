using CommunityToolkit.Mvvm.ComponentModel;

namespace GetStartedApp;

public partial class CompileBindingWindowViewModel : ObservableObject
{
    [ObservableProperty]
    private string _text1 = "Text - 1";
    [ObservableProperty]
    private string _text2 = "Text - 2";
    [ObservableProperty]
    private string _text3 = "Text - 3";
    [ObservableProperty]
    private string _text4 = "Text - 4";
}