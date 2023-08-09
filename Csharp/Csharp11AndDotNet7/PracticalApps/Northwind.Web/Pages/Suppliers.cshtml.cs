using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc;
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
    public IActionResult OnPost()
    {
        if (Supplier is not null && ModelState.IsValid)
        {
            db.Suppliers.Add(Supplier);
            db.SaveChanges();
            return RedirectToPage("/suppliers");
        }
        else
        {
            return Page();
        }
    }
    public IEnumerable<Supplier>? Suppliers { get; set; }
    [BindProperty]
    public Supplier? Supplier { get; set; }
    private NorthwindContext db;
}