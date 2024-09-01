using System.Collections.Generic;
using GetStartedApp.Models;

namespace GetStartedApp.Services;

public class EmployeeService : IEmployeeService
{
    private readonly IDataAccessService<Employee> _employeeService;

    public EmployeeService(IDataAccessService<Employee> employeeService)
    {
        _employeeService = employeeService;
    }
    
    public IEnumerable<Employee> GetEmployees()
    {
        return _employeeService.GetAll() ?? new List<Employee>();
    }
}