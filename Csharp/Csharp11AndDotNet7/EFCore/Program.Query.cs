using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Packt.Shared;

partial class Program
{
    static void QueryingCategories()
    {
        using (Northwind db = new())
        {
            SectionTitle("Categories and how many products they have:");

            IQueryable<Category>? categories;
                // = db.Categories
                // ?.Include( c => c.Products );
            
            WriteLine("Enable eager loading? (Y/N): ");
            bool eagerLoading = ReadKey(intercept: true).Key == ConsoleKey.Y;
            bool explicitLoading = false;
            WriteLine();
            if (eagerLoading)
            {
                categories = db.Categories?.Include( c => c.Products );
            }
            else
            {
                categories = db.Categories;
                WriteLine("Enable explicit loading? (Y/N): ");
                explicitLoading = ReadKey(intercept: true).Key == ConsoleKey.Y;
                WriteLine();
            }

            
            if (categories is not null && categories.Any())
            {
                Info($"QueryString: {categories.ToQueryString()}");

                foreach (Category category in categories)
                {
                    if (explicitLoading)
                    {
                        WriteLine($"Explicitly load products for {category.CategoryName}? (Y/N): ");
                        ConsoleKeyInfo key = ReadKey(intercept: true);
                        WriteLine();

                        if (key.Key == ConsoleKey.Y)
                        {
                            // Load Products for this category explicityly.
                            CollectionEntry<Category, Product> products =
                                db.Entry(category).Collection( c => c.Products );
                            
                            if (!products.IsLoaded)
                            {
                                products.Load();
                            }
                        }
                    }
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
                db.Products?.TagWith("Products filtered by price and sorted.")
                .Where( p => p.Cost >= price ).OrderByDescending( p => p.Cost );
            
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

    static void QueryingWithLike()
    {
        using (Northwind db = new())
        {
            SectionTitle("Pattern matching with LIKE.");

            Write("Enter part of a product name: ");
            string? input = ReadLine();

            if (string.IsNullOrWhiteSpace(input))
            {
                Fail("You didn't enter part of a product name.");
                return;
            }

            IQueryable<Product>? products = 
                db.Products?.TagWith("Like Searching.")
                .Where( p => EF.Functions.Like(input, $"%{input}%") );
            
            if (products is null || !products.Any())
            {
                Fail("No products found.");
                return;
            }

            foreach (Product p in products)
            {
                WriteLine($"Found product {p.ProductName} of {p.Stock} units in stock, {(p.Discontinued ? "discontinued" : "")}");
            }
        }
    }

    static void GetRandomProduct()
    {
        using (Northwind db = new())
        {
            SectionTitle("Get a random row.");

            int? rows = db.Products?.Count();
            if (rows is null || rows == 0)
            {
                Fail("Product table is empty.");
                return;
            }

            Product? product =
                db.Products?.FirstOrDefault( p => p.ProductId == (int)(EF.Functions.Random() * rows) );
            
            if (product is null)
            {
                Fail("Product not found.");
                return;
            }

            WriteLine($"Random product: {product.ProductId} {product.ProductName}");
        }
    }
}