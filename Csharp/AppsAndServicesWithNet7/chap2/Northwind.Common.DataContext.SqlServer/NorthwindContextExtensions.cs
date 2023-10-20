using Microsoft.EntityFrameworkCore; // UseSqlServer
using Microsoft.Extensions.DependencyInjection; // IServiceCollection

namespace Packt.Shared;

public static class NorthwindContextExtensions
{
    public static IServiceCollection AddNorthwindContext(
        this IServiceCollection services,
        string connectionString = "Data Source=.;Initial Catalog=Northwind;Integrated Security=true;TrustServerCertificate=True;"
    )
    {
        services.AddDbContext<NorthwindContext>(options =>
        {
            options.UseSqlServer(connectionString);
            options.LogTo(Console.WriteLine, new [] {
                Microsoft.EntityFrameworkCore.Diagnostics.RelationalEventId.CommandExecuting,
            });
        });
        return services;
    }
}