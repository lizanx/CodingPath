using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Northwind.Mvc.Models;
using Packt.Shared;

namespace Northwind.Mvc.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly NorthwindContext db;

    public HomeController(ILogger<HomeController> logger,
        NorthwindContext injectedContext)
    {
        _logger = logger;
        db = injectedContext;
    }

    public IActionResult Index()
    {
        // _logger.LogError("Logger test: Error");
        // _logger.LogWarning("Logger test: Warning");
        _logger.LogInformation("Logger test: [Info] Index method from HomeController");

        HomeIndexViewModel model = new
        (
            VisitorCount: Random.Shared.Next(1, 1001),
            Categories: db.Categories.ToList(),
            Products: db.Products.ToList()
        );
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
