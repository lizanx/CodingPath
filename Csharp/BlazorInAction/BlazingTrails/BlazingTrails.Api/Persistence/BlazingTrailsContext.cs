using BlazingTrails.Api.Persistence.Entities;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Persistence;

public class BlazingTrailsContext(DbContextOptions<BlazingTrailsContext> options) : DbContext(options)
{
    public DbSet<Trail> Trails { get; set; }
    public DbSet<RouteInstruction> RouteInstructions { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.ApplyConfiguration(new TrailConfig());
        modelBuilder.ApplyConfiguration(new RouteInstructionConfig());
    }
}
