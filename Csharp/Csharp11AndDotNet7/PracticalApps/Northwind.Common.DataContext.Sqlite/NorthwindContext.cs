using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace Packt.Shared;

public partial class NorthwindContext : DbContext
{
    public NorthwindContext()
    {
    }

    public NorthwindContext(DbContextOptions<NorthwindContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Category> Categories { get; set; }

    public virtual DbSet<Customer> Customers { get; set; }

    public virtual DbSet<Employee> Employees { get; set; }

    public virtual DbSet<EmployeeTerritory> EmployeeTerritories { get; set; }

    public virtual DbSet<Order> Orders { get; set; }

    public virtual DbSet<OrderDetail> OrderDetails { get; set; }

    public virtual DbSet<Product> Products { get; set; }

    public virtual DbSet<Shipper> Shippers { get; set; }

    public virtual DbSet<Supplier> Suppliers { get; set; }

    public virtual DbSet<Territory> Territories { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        // Adjust db file path for VS and VScode.
        string workDir = Environment.CurrentDirectory;
        string path = string.Empty;

        if (workDir.EndsWith("net7.0"))
        {
            // Visual Studio
            // Running in the <project>\bin\<Debug|Release>\net7.0 directory.
            path = Path.Combine("..", "..", "..", "..", "Northwind.db");
        }
        else
        {
            // Visual Studio Code
            path = Path.Combine("..", "Northwind.db");
        }

        optionsBuilder.UseSqlite($"Filename={path}");
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<OrderDetail>(entity =>
        {
            entity.HasKey(e => new { e.OrderId, e.ProductId });

            entity.HasOne(d => d.Order)
                    .WithMany(p => p.OrderDetails)
                    .HasForeignKey(d => d.OrderId)
                    .OnDelete(DeleteBehavior.ClientSetNull);

            entity.HasOne(d => d.Product)
                    .WithMany(p => p.OrderDetails)
                    .HasForeignKey(d => d.ProductId)
                    .OnDelete(DeleteBehavior.ClientSetNull);
        });

        modelBuilder.Entity<Product>()
            .Property(product => product.UnitPrice)
            .HasConversion<double>();
        
        // TODO: handle exceptions when deleting a Customer.
        // modelBuilder.Entity<Customer>(entity =>
        // {
        //     entity.HasMany(c => c.Orders)
        //         .WithOne()
        //         .OnDelete(DeleteBehavior.Cascade);
        // });
        // modelBuilder.Entity<Order>(entity =>
        // {
        //     entity.HasOne(o => o.Customer)
        //             .WithMany(c => c.Orders)
        //             .HasForeignKey(o => o.CustomerId)
        //             .OnDelete(DeleteBehavior.Cascade);
        // });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
