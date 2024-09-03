using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Models;

namespace GetStartedApp.ViewModels;

public partial class EmployeeViewModel : ObservableObject
{
    [ObservableProperty] private string _firstName;
    [ObservableProperty] private string _lastName;
    [ObservableProperty] private string _career;
    [ObservableProperty] private int _age;
    [ObservableProperty] private double _salary;

    public EmployeeViewModel(Employee employee)
    {
        FirstName = employee.FirstName;
        LastName = employee.LastName;
        Career = employee.Career;
        Age = employee.Age;
        Salary = employee.Salary;
    }
}