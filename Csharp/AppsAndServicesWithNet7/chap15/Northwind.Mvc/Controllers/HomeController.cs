using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Northwind.Mvc.Models;
using Microsoft.EntityFrameworkCore;
using Packt.Shared;

namespace Northwind.Mvc.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly NorthwindContext db;

    public HomeController(ILogger<HomeController> logger,
        NorthwindContext db)
    {
        _logger = logger;
        this.db = db;
    }

    public IActionResult Index()
    {
        IEnumerable<Order> model = db.Orders
            .Include(order => order.Customer)
            .Include(order => order.OrderDetails)
            .OrderByDescending(order => order.OrderDetails
                .Sum(detail => detail.Quantity * detail.UnitPrice))
            .AsEnumerable();
        
        return View(model);
    }

    public IActionResult Privacy()
    {
        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
