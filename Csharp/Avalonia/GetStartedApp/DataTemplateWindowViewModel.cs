using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;

namespace GetStartedApp;

public partial class DataTemplateWindowViewModel : ObservableObject
{
    [ObservableProperty]
    private string _listTitle = "Some Popular Programming Languages";
    [ObservableProperty]
    private ObservableCollection<ProgrammingLanguageItemViewModel> _programmingLanguages =
    [
        new ProgrammingLanguageItemViewModel { LanguageName = "C", LanguageType = ProgrammingLanguageItemViewModel.ExecutionType.NativeCompiled },
        new ProgrammingLanguageItemViewModel
        {
            LanguageName = "C++", LanguageType = ProgrammingLanguageItemViewModel.ExecutionType.NativeCompiled
        },
        new ProgrammingLanguageItemViewModel
        {
            LanguageName = "C#", LanguageType = ProgrammingLanguageItemViewModel.ExecutionType.IntermediateCompiled
        },
        new ProgrammingLanguageItemViewModel { LanguageName = "Python", LanguageType = ProgrammingLanguageItemViewModel.ExecutionType.Interpreted }
    ];
}

public partial class ProgrammingLanguageItemViewModel : ObservableObject
{
    public enum ExecutionType
    {
        NativeCompiled,
        IntermediateCompiled,
        Interpreted,
    }
    [ObservableProperty]
    private string _languageName = string.Empty;
    [ObservableProperty]
    private ExecutionType _languageType = ExecutionType.NativeCompiled;
    public bool IsNative => LanguageType == ExecutionType.NativeCompiled;
}
