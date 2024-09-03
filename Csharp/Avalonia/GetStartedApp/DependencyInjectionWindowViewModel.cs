using System.Collections.ObjectModel;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Models;
using GetStartedApp.Services;
using GetStartedApp.ViewModels;
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
