using BlazingTrails.Api.Persistence;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Features.ManageTrails.EditTrail;

public static class GetTrailEndpoint
{
    public static async Task<IResult> GetTrail([FromRoute] int trailId, BlazingTrailsContext db, CancellationToken cancellationToken= default)
    {
        var trail = await db.Trails.
            Include(t => t.Route)
            .SingleOrDefaultAsync(t => t.Id == trailId, cancellationToken: cancellationToken);
        if (trail == null)
        {
            return Results.BadRequest("Trail couldn't be found.");
        }

        var response = new GetTrailRequest.Response(
            new GetTrailRequest.Trail(
                trail.Id,
                trail.Name,
                trail.Location,
                trail.Image,
                trail.TimeInMinutes,
                trail.Length,
                trail.Description,
                trail.Route.Select(ri => new GetTrailRequest.RouteInstruction(ri.Id, ri.Stage, ri.Description))
            )
        );

        return Results.Ok(response);
    }
}
