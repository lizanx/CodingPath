using CarInfo.Model;
using Microsoft.EntityFrameworkCore;

namespace CarInfo.Persistence;

public class CarDbContext : DbContext
{
    public CarDbContext(DbContextOptions<CarDbContext> options) : base(options)
    {}

    public DbSet<Car> Cars { get; set; }
}
