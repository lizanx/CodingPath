using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BlazingTrails.Api.Persistence.Entities;

public class Trail
{
    public int Id { get; set; }
    public string Name { get; set; } = default!;
    public string Description { get; set; } = default!;
    public string? Image { get; set; }
    public string Location { get; set; } = default!;
    public int TimeInMinutes { get; set; }
    public int Length { get; set; }
    // TODO: cannot get httpContext.User.Identity?.Name, temporarily add owner here.
    // public string Owner { get; set; } = default!;
    public string? Owner { get; set; }
    public ICollection<Waypoint> Waypoints { get; set; } = default!;
}

public class TrailConfig : IEntityTypeConfiguration<Trail>
{
    public void Configure(EntityTypeBuilder<Trail> builder)
    {
        builder.Property(x => x.Name).IsRequired();
        builder.Property(x => x.Description).IsRequired();
        builder.Property(x => x.Location).IsRequired();
        builder.Property(x => x.TimeInMinutes).IsRequired();
        builder.Property(x => x.Length).IsRequired();
        // TODO: cannot get httpContext.User.Identity?.Name, temporarily disable DB requirement here
        // builder.Property(x => x.Owner).IsRequired();
    }
}
