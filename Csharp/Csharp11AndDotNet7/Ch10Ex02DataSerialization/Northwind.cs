using Microsoft.EntityFrameworkCore;

namespace Packt.Shared;

class Northwind : DbContext
{
    public DbSet<Category>? Categories { get; set; }
    public DbSet<Product>? Products { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        base.OnConfiguring(optionsBuilder);

        string connection = $"Filename={Path.Combine(Environment.CurrentDirectory, "Northwind.db")}";
        Logging.Info($"Connecting: {connection}...");

        optionsBuilder.UseSqlite(connection);
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        if (Database.ProviderName?.Contains("Sqlite") ?? false)
        {
            modelBuilder.Entity<Product>()
                .Property( p => p.UnitPrice )
                .HasConversion<double>();
            
            Logging.Info("Conversion of Product.UnitPrice from decimal to double enabled.");
        }

        modelBuilder.Entity<Product>()
            .HasQueryFilter( p => !p.Discontinued );
    }
}