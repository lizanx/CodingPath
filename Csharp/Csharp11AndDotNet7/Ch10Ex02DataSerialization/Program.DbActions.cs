using Microsoft.EntityFrameworkCore;
using Packt.Shared;

partial class Program
{
    public static Category[]? QueryCategoryWithProducts()
    {
        // Always use eager loading.
        using (Northwind db = new())
        {
            return db.Categories?.Include( c => c.Products ).ToArray();
        }
    }
}