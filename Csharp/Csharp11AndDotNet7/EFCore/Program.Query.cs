using Microsoft.EntityFrameworkCore;
using Packt.Shared;

partial class Program
{
    static void QueryingCategories()
    {
        using (Northwind db = new())
        {
            SectionTitle("Categories and how many products they have:");

            IQueryable<Category>? categories =
                db.Categories?.Include( c => c.Products );
            
            if (categories is not null && categories.Any())
            {
                Info($"QueryString: {categories.ToQueryString()}");

                foreach (Category category in categories)
                {
                    WriteLine($"{category.CategoryName} has {category.Products.Count} products.");
                }
            }
            else
            {
                Fail("No categories found.");
                return;
            }
        }
    }

    static void FilteredIncludes()
    {
        using (Northwind db = new())
        {
            SectionTitle("Products with a minimum number of units in stock.");

            string? input;
            int stock;
            do
            {
                Write("Enter a minimum for units in stock: ");
                input = ReadLine();
            } while (!int.TryParse(input, out stock));

            IQueryable<Category>? categories =
                db.Categories?.Include( c => c.Products.Where( p => p.Stock >= stock) );
            
            if (categories is null || !categories.Any())
            {
                Fail("No categories found.");
                return;
            }

            Info($"QueryString: {categories.ToQueryString()}");

            foreach (Category c in categories)
            {
                WriteLine($"Category {c.CategoryName} has {c.Products.Count} products with " +
                    $"a minimum of {stock} units in stock.");
                
                foreach (Product p in c.Products)
                {
                    WriteLine($"\t{p.ProductName} has {p.Stock} units in stock.");
                }
            }
        }
    }

    static void QueryingProducts()
    {
        using (Northwind db = new())
        {
            SectionTitle("Products that cost more than a price, highest at top.");

            string? input;
            decimal price;
            do
            {
                Write("Enter a product price: ");
                input = ReadLine();
            } while(!decimal.TryParse(input, out price));

            IQueryable<Product>? products =
                db.Products?.Where( p => p.Cost >= price ).OrderByDescending( p => p.Cost );
            
            if (products is null || !products.Any())
            {
                Fail("No products found.");
                return;
            }

            Info($"QueryString: {products.ToQueryString()}");

            foreach (Product p in products)
            {
                WriteLine($"{p.ProductId}: {p.ProductName} costs {p.Cost:$#, ##0.00} and has {p.Stock} units in stock.");
            }
        }
    }
}