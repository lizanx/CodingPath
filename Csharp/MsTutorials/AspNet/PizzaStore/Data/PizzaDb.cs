using Microsoft.EntityFrameworkCore;
using PizzaStore.Models;

namespace PizzaStore.Data;

public class PizzaDb(DbContextOptions options) : DbContext(options)
{
    public DbSet<Pizza> Pizzas { get; set; } = null!;
}
