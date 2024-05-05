using BlazingTrails.Api.Persistence;
using BlazingTrails.Shared.Features.Home.Shared;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Features.Home.Shared;

public static class GetTrailsEndpoint
{
    public static async Task<IResult> GetTrails(BlazingTrailsContext db, CancellationToken cancellationToken = default)
    {
        var trails = await db.Trails
            .Include(t => t.Waypoints)
            .ToListAsync(cancellationToken);
        
        var response = new GetTrailsRequest.Response(trails.Select(t =>
            new GetTrailsRequest.Trail(t.Id, t.Name, t.Image, t.Location, t.TimeInMinutes,
                t.Length, t.Description, t.Owner ?? "Anonymous", t.Waypoints.Select(wp =>
                    new GetTrailsRequest.Waypoint(wp.Latitude, wp.Longitude)).ToList())));
        return Results.Ok(response);
    }
}
