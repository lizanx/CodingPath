using System.Collections.ObjectModel;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Services;

namespace GetStartedApp.ViewModels;

public partial class TableWindowViewModel : ObservableObject
{
    [ObservableProperty] private ObservableCollection<EmployeeViewModel> _employees;

    public TableWindowViewModel(IEmployeeService employeeService)
    {
        _employees =
            new ObservableCollection<EmployeeViewModel>(employeeService.GetEmployees()
                .Select(e => new EmployeeViewModel(e)));
    }
}