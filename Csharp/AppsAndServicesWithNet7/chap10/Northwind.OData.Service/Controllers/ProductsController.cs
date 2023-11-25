using Microsoft.AspNetCore.Mvc; // IActionResult
using Microsoft.AspNetCore.OData.Query; // [EnableQuery]
using Microsoft.AspNetCore.OData.Routing.Controllers; // ODataController

using Packt.Shared; // NorthwindContext

namespace Northwind.OData.Service.Controllers;

public class ProductsController : ODataController
{
    protected readonly NorthwindContext db;

    public ProductsController(NorthwindContext db)
    {
        this.db = db;
    }

    [EnableQuery]
    public IActionResult Get(string version = "1")
    {
        Console.WriteLine($"*** ProductsController version {version}.");

        return Ok(db.Products);
    }

    [EnableQuery]
    public IActionResult Get(int key, string version = "1")
    {
        Console.WriteLine($"*** ProductsController version {version}.");

        IQueryable<Product> products = db.Products.Where(
            p => p.ProductId == key
        );
        Product? product = products.FirstOrDefault();

        if ((products is null) || (product is null))
        {
            return NotFound($"Product with id {key} not found.");
        }

        if (version == "2")
        {
            product.ProductName += "version 2.0";
        }

        return Ok(product);
    }
}