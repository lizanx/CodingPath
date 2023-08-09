using Microsoft.EntityFrameworkCore;
using Packt.Shared;

using (Northwind db = new())
{
    WriteLine("Cities where Northwind's customers locate in:");
    IQueryable<string?> cities = db.Customers.Select( c => c.City ).Distinct();
    foreach (string? city in cities)
    {
        if (city is not null)
        {
            WriteLine($"\t{city}");
        }
    }

    while (true)
    {
        Write("Enter a city name to list companies which are Northwind customers(Press ENTER directly to exit): ");
        string? input = ReadLine();
        if (string.IsNullOrWhiteSpace(input))
        {
            WriteLine("Exit.");
            break;
        }

        IQueryable<string>? companies = db.Customers
            .Where( c => c.City != null && c.City.ToLower() == input.Trim().ToLower() )
            .Select( c => c.CompanyName );
        if (companies is null || !companies.Any())
        {
            WriteLine("No matched companies found.");
            continue;
        }
        foreach (string company in companies)
        {
            WriteLine($"\t{company}");
        }
    }
}