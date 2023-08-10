using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;

using Packt.Shared;

namespace Northwind.Web.Pages.CustomerDetails;

public class CustomerDetailsModel : PageModel
{
    public CustomerDetailsModel(NorthwindContext injectedContext)
    {
        db = injectedContext;
    }

    public void OnGet()
    {
        ViewData["Title"] = "Northwind B2B - Customer Details";

        string id = HttpContext.Request.Query["id"]!;
        Customer = db.Customers.Include( c => c.Orders ).FirstOrDefault( c => c.CustomerId == id );
    }

    public Customer? Customer { get; set; }

    private NorthwindContext db;
}