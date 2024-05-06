using BlazingTrails.Api.Persistence;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Features.ManageTrails.EditTrail;

public static class GetTrailEndpoint
{
    public static async Task<IResult> GetTrail([FromRoute] int trailId, BlazingTrailsContext db,
        HttpContext httpContext, CancellationToken cancellationToken = default)
    {
        var trail = await db.Trails
            .Include(t => t.Waypoints)
            .SingleOrDefaultAsync(t => t.Id == trailId, cancellationToken: cancellationToken);
        if (trail == null)
        {
            return Results.BadRequest("Trail couldn't be found.");
        }

        // [BUG]: access tokens cannot be passed from client, skip verification here.
        // if (!httpContext.User.IsInRole("Administrator") &&
        //     trail.Owner != null && !trail.Owner.Equals(httpContext.User.Identity?.Name, StringComparison.OrdinalIgnoreCase))
        // {
        //     return Results.Unauthorized();
        // }

        var response = new GetTrailRequest.Response(
            new GetTrailRequest.Trail(
                trail.Id,
                trail.Name,
                trail.Location,
                trail.Image,
                trail.TimeInMinutes,
                trail.Length,
                trail.Description,
                trail.Waypoints.Select(wp => new GetTrailRequest.Waypoint(wp.Latitude, wp.Longitude))
            )
        );

        return Results.Ok(response);
    }
}
