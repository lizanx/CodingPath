using Packt.Shared;

namespace Northwind.GraphQL;

public record class AddProductInput(
    string ProductName,
    int? SupplierId,
    int? CategoryId,
    string QuantityPerUnit,
    decimal? UnitPrice,
    short? UnitsInStock,
    short? UnitsOnOrder,
    short? ReorderLevel,
    bool Discontinued
);

public class AddProductPayload
{
    public Product Product { get; set; }

    public AddProductPayload(Product product)
    {
        Product = product;
    }
}

public class Mutation
{
    public async Task<AddProductPayload> AddProductAsync(
        AddProductInput input, NorthwindContext db)
    {
        Product product = new()
        {
            ProductName = input.ProductName,
            SupplierId = input.SupplierId,
            CategoryId = input.CategoryId,
            QuantityPerUnit = input.QuantityPerUnit,
            UnitPrice = input.UnitPrice,
            UnitsInStock = input.UnitsInStock,
            UnitsOnOrder = input.UnitsOnOrder,
            ReorderLevel = input.ReorderLevel,
            Discontinued = input.Discontinued
        };

        db.Products.Add(product);

        int afffectedRows = await db.SaveChangesAsync();

        return new AddProductPayload(product);
    }
}