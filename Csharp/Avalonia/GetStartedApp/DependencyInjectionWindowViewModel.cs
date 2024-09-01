using System.Collections.ObjectModel;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Models;
using GetStartedApp.Services;
using Microsoft.Extensions.DependencyInjection;

namespace GetStartedApp;

public partial class DependencyInjectionWindowViewModel : ObservableObject
{
    [ObservableProperty] private ObservableCollection<EmployeeViewModel> _employees;

    public DependencyInjectionWindowViewModel(IEmployeeService employeeService)
    {
        _employees = new ObservableCollection<EmployeeViewModel>(
            employeeService.GetEmployees().Select(e => new EmployeeViewModel(e)));
    }
}

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