using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using Microsoft.EntityFrameworkCore;
using Northwind.Mvc.Models;
using Packt.Shared;

namespace Northwind.Mvc.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly NorthwindContext db;
    private readonly IHttpClientFactory clientFactory;

    public HomeController(
        ILogger<HomeController> logger,
        NorthwindContext injectedContext,
        IHttpClientFactory httpClientFactory)
    {
        _logger = logger;
        db = injectedContext;
        clientFactory = httpClientFactory;
    }

    public async Task<IActionResult> Customers(string country)
    {
        string uri;
        if (string.IsNullOrEmpty(country))
        {
            ViewData["Title"] = "All Customers Worldwide";
            uri = "api/customers";
        }
        else
        {
            ViewData["Title"] = $"Customers in country {country}";
            uri = $"api/customers/?country={country}";
        }

        HttpClient client = clientFactory.CreateClient(name: "Northwind.WebApi");
        HttpRequestMessage request = new(method: HttpMethod.Get, requestUri: uri);
        HttpResponseMessage response = await client.SendAsync(request);
        IEnumerable<Customer>? model = await response.Content.ReadFromJsonAsync<IEnumerable<Customer>>();

        return View(model);
    }

    [ResponseCache(Duration = 10, Location = ResponseCacheLocation.Any)]
    public async Task<IActionResult> Index()
    {
        // _logger.LogError("Logger test: Error");
        // _logger.LogWarning("Logger test: Warning");
        _logger.LogInformation("Logger test: [Info] Index method from HomeController");

        HomeIndexViewModel model = new
        (
            VisitorCount: Random.Shared.Next(1, 1001),
            Categories: await db.Categories.ToListAsync(),
            Products: await db.Products.ToListAsync()
        );
        return View(model);
    }

    public async Task<IActionResult> ProductDetail(int? id, string alertstyle = "success")
    {
        ViewData["alertstyle"] = alertstyle;

        if (!id.HasValue)
        {
            return BadRequest("You must pass a product ID in route, for example, /Home/ProductDetail/21");
        }

        Product? model = await db.Products.SingleOrDefaultAsync( p => p.ProductId == id );
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

    public IActionResult ProductsThatCostMoreThan(decimal? price)
    {
        if (!price.HasValue)
        {
            return BadRequest("You must pass a prodcut price in the query string, " +
                "for example, /home/ProductsThatCostMoreThan/?price=50");
        }
        IEnumerable<Product> model = db.Products
            .Include(p => p.Category)
            .Include(p => p.Supplier)
            .Where(p => p.UnitPrice > price);
        if (!model.Any())
        {
            return NotFound($"No products cost more than {price}.");
        }
        ViewData["MaxPrice"] = price.Value.ToString("C");
        return View(model);
    }

    public async Task<IActionResult> Category(int? id)
    {
        if (!id.HasValue)
        {
            return BadRequest("You must pass a category id in route, for example, /Home/Category/2.");
        }

        Category? model = await db.Categories.SingleOrDefaultAsync( c => c.CategoryId == id );
        if (model is null)
        {
            return NotFound($"Category {id} not found.");
        }

        return View(model);
    }
}
