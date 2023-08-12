using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
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

    [ResponseCache(Duration = 10, Location = ResponseCacheLocation.Any)]
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

    public IActionResult ProductDetail(int? id, string alertstyle = "success")
    {
        ViewData["alertstyle"] = alertstyle;
        
        if (!id.HasValue)
        {
            return BadRequest("You must pass a product ID in route, for example, /Home/ProductDetail/21");
        }

        Product? model = db.Products.SingleOrDefault( p => p.ProductId == id );
        if (model is null)
        {
            return NotFound($"Product {id} not found.");
        }

        return View(model);
    }

    public IActionResult ModelBinding()
    {
        return View(); // the page with a form to submit
    }

    [HttpPost]
    public IActionResult ModelBinding(Thing thing)
    {
        // return View(thing);

        HomeModelBindingViewModel model = new(
            thing,
            !ModelState.IsValid,
            ModelState.Values.SelectMany(state => state.Errors).Select(err => err.ErrorMessage)
        );

        return View(model);
    }

    [Route("Private")]
    [Authorize(Roles = "Administrators")]
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
