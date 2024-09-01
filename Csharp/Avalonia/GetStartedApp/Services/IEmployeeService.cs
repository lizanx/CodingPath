using System.Collections.Generic;
using GetStartedApp.Models;

namespace GetStartedApp.Services;

public interface IEmployeeService
{
    IEnumerable<Employee> GetEmployees();
}
