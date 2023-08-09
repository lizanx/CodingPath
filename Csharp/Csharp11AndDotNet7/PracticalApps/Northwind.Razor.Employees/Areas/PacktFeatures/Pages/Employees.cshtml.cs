using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Packt.Shared;

namespace PacktFeatures.Pages;

public class EmployeesPageModel : PageModel
{
    public EmployeesPageModel(NorthwindContext injectedContext)
    {
        db = injectedContext;
    }
    public void OnGet()
    {
        ViewData["Title"] = "Northwind B2B - Employees";
        Employees = db.Employees
            .OrderBy( e => e.LastName )
            .ThenBy( e => e.FirstName )
            .ToArray();
    }
    public Employee[] Employees = null!;
    private NorthwindContext db;
}
