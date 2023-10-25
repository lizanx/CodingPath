using Microsoft.Data.SqlClient;
using Microsoft.EntityFrameworkCore;
using Packt.Shared;
using System.Data;

// Retrieve all products using ADO.NET
Console.WriteLine($"----- Test With ADO.NET -----");
var adoStart = DateTime.Now;
SqlConnectionStringBuilder builder = new()
{
    InitialCatalog = "Northwind",
    MultipleActiveResultSets = true,
    Encrypt = true,
    TrustServerCertificate = true,
    ConnectTimeout = 10,
    IntegratedSecurity = true,
    DataSource = ".",
};
SqlConnection connection = new(builder.ConnectionString);
await connection.OpenAsync();
SqlCommand sqlCommand = connection.CreateCommand();
sqlCommand.CommandType = CommandType.Text;
sqlCommand.CommandText = "SELECT * FROM Products";
SqlDataReader reader = await sqlCommand.ExecuteReaderAsync();
while (reader.Read())
{
    Console.WriteLine("| {0,5} | {1,-35} | {2,8:C} |",
        await reader.GetFieldValueAsync<int>("ProductId"),
        await reader.GetFieldValueAsync<string>("ProductName"),
        await reader.GetFieldValueAsync<decimal>("UnitPrice"));
}
await reader.CloseAsync();
await connection.CloseAsync();
var adoEnd = DateTime.Now;
Console.WriteLine();

// Test with EFCore.
Console.WriteLine("----- Test With EFCore -----");
var efStart = DateTime.Now;
DbContextOptionsBuilder<NorthwindContext> optionsBuilder = new();
optionsBuilder.UseSqlServer("Data Source=.;Initial Catalog=Northwind;Integrated Security=true;TrustServerCertificate=True;");
using (NorthwindContext db = new(optionsBuilder.Options))
{
    foreach (Product p in db.Products)
    {
        Console.WriteLine("| {0,5} | {1,-35} | {2,8:C} |",
            p.ProductId, p.ProductName, p.UnitPrice);
    }
}
var efEnd = DateTime.Now;

Console.WriteLine("\n\n----- Time Consumption Comparation -----");
Console.WriteLine("ADO.NET consumes {0}ms", (adoEnd - adoStart).TotalMilliseconds);
Console.WriteLine("EFCore consumes {0}ms", (efEnd - efStart).TotalMilliseconds);
