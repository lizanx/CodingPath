using Microsoft.AspNetCore.Mvc.RazorPages;
using Packt.Shared;

namespace Northwind.Web.Pages;

public class SuppliersModel : PageModel
{
    public SuppliersModel(NorthwindContext injectedContext)
    {
        db = injectedContext;
    }

    public void OnGet()
    {
        ViewData["Title"] = "Northwind B2B - Suppliers";

        Suppliers = db.Suppliers
            .OrderBy( s => s.Country )
            .ThenBy( s => s.CompanyName );
    }
    public IEnumerable<Supplier>? Suppliers { get; set; }

    private NorthwindContext db;
}