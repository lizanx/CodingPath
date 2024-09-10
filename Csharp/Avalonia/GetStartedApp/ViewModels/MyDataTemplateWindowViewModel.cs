using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Models;

namespace GetStartedApp.ViewModels;

public partial class MyDataTemplateWindowViewModel : ObservableObject
{
    [ObservableProperty] private Employee _employee = new()
    {
        FirstName = "John",
        LastName = "Smith",
        Career = "Actor",
        Age = 48,
        Salary = 100_000
    };
}
