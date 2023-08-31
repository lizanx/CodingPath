using Microsoft.EntityFrameworkCore;
using Cooking.Data;

namespace Cooking.Services;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options) {}
    
    public DbSet<Recipe> Recipes { get; set; }
}
