using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Diagnostics;

namespace Packt.Shared;

public class Northwind : DbContext
{
    // These properties map to tables in the database.
    public DbSet<Category>? Categories { get; set; }
    public DbSet<Product>? Products { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);

        modelBuilder.Entity<Category>()
            .Property(category => category.CategoryName)
            .IsRequired()
            .HasMaxLength(15);
        
        if (Database.ProviderName?.Contains("Sqlite") ?? false)
        {
            modelBuilder.Entity<Product>()
                .Property(product => product.Cost)
                .HasConversion<double>();
        }

        modelBuilder.Entity<Product>()
            .HasQueryFilter( p => !p.Discontinued );
    }
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        string dbFilePath = Path.Combine(Environment.CurrentDirectory, "Northwind.db");

        string connection = $"Filename={dbFilePath}";

        // ColoredLog.Warn($"Connection: {connection}");
        optionsBuilder.UseSqlite(connection);


        // optionsBuilder.LogTo(WriteLine, // Console
        //     new[] { RelationalEventId.CommandExecuting }) 
        //     .EnableSensitiveDataLogging();
        // optionsBuilder.UseLazyLoadingProxies();
    }
}