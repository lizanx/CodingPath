using CommunityToolkit.Mvvm.ComponentModel;

namespace GetStartedApp.ViewModels;

public partial class CompilerViewModel : ObservableObject
{
    [ObservableProperty] private string _compilerType = string.Empty;
    [ObservableProperty] private string _compilerName = string.Empty;
}