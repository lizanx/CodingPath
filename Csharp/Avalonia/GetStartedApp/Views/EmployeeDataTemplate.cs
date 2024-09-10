using Avalonia.Controls;
using Avalonia.Controls.Templates;
using Avalonia.Layout;
using GetStartedApp.Models;

namespace GetStartedApp.Views;

public class EmployeeDataTemplate : IDataTemplate
{
    public Control Build(object? arg)
    {
        Employee employee = (arg as Employee)!;
        return new StackPanel()
        {
            Orientation = Orientation.Vertical,
            Spacing = 10,
            Children =
            {
                new TextBlock() { Text = $"First Name: {employee.FirstName}" },
                new TextBlock() { Text = $"Last Name: {employee.LastName}" },
                new TextBlock() { Text = $"Career: {employee.Career}" },
                new TextBlock() { Text = $"Salary: {employee.Salary}" },
            }
        };
    }

    public bool Match(object? data) =>
        data is Employee;
}