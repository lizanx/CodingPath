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

    public IActionResult Post([FromBody]Product product)
    {
        db.Products.Add(product);
        db.SaveChanges();
        return Created(product);
    }

    public IActionResult Put([FromBody]Product product)
    {
        if (db.Products.FirstOrDefault(p => p.ProductId == product.ProductId)
            is Product)
        {
            db.Products.Update(product);
            db.SaveChanges();
            return Updated(product);
        }
        return NotFound();
    }

    public IActionResult Delete([FromRoute]int id)
    {
        if (db.Products.FirstOrDefault(p => p.ProductId == id) is Product product)
        {
            db.Products.Remove(product);
            db.SaveChanges();
            return NoContent();
        }
        return NotFound();
    }
}