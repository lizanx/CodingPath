using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Storage;
using Packt.Shared;

partial class Program
{
    static void ListProducts(int[]? productIdsToHighlight = null)
    {
        using (Northwind db = new())
        {
            if (db.Products is null || !db.Products.Any())
            {
                Fail("There are no products.");
                return;
            }

            WriteLine($"| {"ID", -3} | {"Product Name", -35} | {"Cost", 8} | "
                + $"{"Stock", 5} | Disc. | ");
            
            foreach (Product p in db.Products)
            {
                ConsoleColor prevColor = ForegroundColor;

                if (productIdsToHighlight is not null &&
                    productIdsToHighlight.Contains(p.ProductId))
                {
                    ForegroundColor = ConsoleColor.Green;
                }
                WriteLine("| {0:000} | {1,-35} | {2,8:$#,##0.00} | {3,5} | {4} |",
                    p.ProductId, p.ProductName, p.Cost, p.Stock, p.Discontinued);

                ForegroundColor = prevColor;
            }
        }
    }

    static (int affected, int productId) AddProduct(
        int categoryId, string productName, decimal? price)
    {
        using (Northwind db = new())
        {
            if (db.Products is null)
            {
                return (0, 0);
            }

            Product p = new()
            {
                CategoryId = categoryId,
                ProductName = productName,
                Cost = price,
                Stock = 72
            };

            EntityEntry<Product> entity = db.Products.Add(p);
            WriteLine($"State: {entity.State}, ProductId: {p.ProductId}");

            int affected = db.SaveChanges();
            WriteLine($"State: {entity.State}, ProductId: {p.ProductId}");

            return (affected, p.ProductId);
        }
    }

    static (int affected, int productId) IncreaseProductPrice(
        string productNameStartsWith, decimal amount)
    {
        using (Northwind db = new())
        {
            if (db.Products is null || !db.Products.Any())
            {
                Fail("There are no products in db.");
                return (0, 0);
            }

            Product updateProduct = db.Products.First( p => p.ProductName.StartsWith(productNameStartsWith) );
            updateProduct.Cost += amount;
            
            int affected = db.SaveChanges();

            return (affected, updateProduct.ProductId);
        }
    }

    static int DeleteProducts(string productNameStartsWith)
    {
        using (Northwind db = new())
        {
            using (IDbContextTransaction t = db.Database.BeginTransaction())
            {
                WriteLine($"Transaction isolation level: {t.GetDbTransaction().IsolationLevel}");

                IQueryable<Product>? products = db.Products?.Where(
                    p => p.ProductName.StartsWith(productNameStartsWith)
                );

                if (products is null || !products.Any())
                {
                    WriteLine("No products found to delete.");
                    return 0;
                }
                else
                {
                    if (db.Products is null)
                    {
                        return 0;
                    }

                    db.Products.RemoveRange(products);
                }
                
                int affected = db.SaveChanges();

                t.Commit();

                return affected;
            }
        }
    }

    static (int affected, int[]? productIds) IncreaseProductPriceBetter(
        string productNameStartsWith, decimal amount)
    {
        using (Northwind db = new())
        {
            IQueryable<Product>? products = db.Products?.Where( p => p.ProductName.StartsWith(productNameStartsWith) );
            if (products is null || !products.Any())
            {
                Fail("No products found.");
                return (0, null);
            }

            int affected = products.ExecuteUpdate( s => s.SetProperty( p => p.Cost, p => p.Cost + amount ));

            return (affected, products.Select( p => p.ProductId ).ToArray());
        }
    }

    static int DeleteProductsBetter(string productNameStartsWith)
    {
        using (Northwind db = new())
        {
            IQueryable<Product>? products = db.Products?.Where( p => p.ProductName.StartsWith(productNameStartsWith) );
            if (products is null || !products.Any())
            {
                Fail("No products found.");
                return 0;
            }

            return products.ExecuteDelete();
        }
    }
}