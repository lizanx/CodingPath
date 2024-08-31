using System.Threading.Tasks;
using Avalonia.Controls;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace GetStartedApp;

public partial class FilePickerWindowViewModel : ObservableObject
{
    [ObservableProperty] private string _userInputString = string.Empty;
    [ObservableProperty] private string _fileContentString = string.Empty;
}