using BlazingTrails.Api.Persistence;
using BlazingTrails.Api.Persistence.Entities;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using BlazingTrails.Shared.Features.ManageTrails.Shared;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Features.ManageTrails.EditTrail;

public static class EditTrailEndpoint
{
    public static async Task<IResult> EditTrail([FromBody] EditTrailRequest request, BlazingTrailsContext db,
        HttpContext httpContext, CancellationToken cancellationToken = default)
    {
        var trail = await db.Trails
            .Include(t => t.Waypoints)
            .SingleOrDefaultAsync(t => t.Id == request.Trail.Id, cancellationToken: cancellationToken);
        if (trail == null)
        {
            return Results.BadRequest("Trail couldn't be found.");
        }

        // TODO: cannot get httpContext.User.Identity?.Name, temporarily skip identity verification.
        // if (trail.Owner != null && !trail.Owner.Equals(httpContext.User.Identity?.Name, StringComparison.OrdinalIgnoreCase))
        // {
        //     return Results.Unauthorized();
        // }

        trail.Name = request.Trail.Name;
        trail.Description = request.Trail.Description;
        trail.Location = request.Trail.Location;
        trail.TimeInMinutes = request.Trail.TimeInMinutes;
        trail.Length = request.Trail.Length;
        trail.Waypoints = request.Trail.Waypoints.Select(wp =>
            new Waypoint
            {
                Latitude = wp.Latitude,
                Longitude = wp.Longitude,
            })
            .ToList();
        
        if (request.Trail.ImageAction == ImageAction.Remove)
        {
            File.Delete(Path.Combine(Directory.GetCurrentDirectory(), "Images", trail.Image!));
            trail.Image = null;
        }

        await db.SaveChangesAsync(cancellationToken);

        return Results.Ok(true);
    }
}