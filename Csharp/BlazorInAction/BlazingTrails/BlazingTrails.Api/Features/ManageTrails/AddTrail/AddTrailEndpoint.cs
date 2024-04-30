using BlazingTrails.Shared.Features.ManageTrails.AddTrail;
using BlazingTrails.Api.Persistence;
using BlazingTrails.Api.Persistence.Entities;
using Microsoft.AspNetCore.Mvc;

namespace BlazingTrails.Api.Features.ManageTrails.AddTrail;

public static class AddTrailEndpoint
{
    public static async Task<IResult> AddTrail([FromBody] AddTrailRequest request, BlazingTrailsContext db)
    {
        Trail trail = new() {
            Name = request.Trail.Name,
            Description = request.Trail.Description,
            Location = request.Trail.Location,
            TimeInMinutes = request.Trail.TimeInMinutes,
            Length = request.Trail.Length,
        };
        await db.Trails.AddAsync(trail);
        
        var routeInstructions = request.Trail.Route.Select(x => new RouteInstruction()
            {
                Stage = x.Stage,
                Description = x.Description,
                Trail = trail
            });
        await db.RouteInstructions.AddRangeAsync(routeInstructions);

        await db.SaveChangesAsync();

        return Results.Ok(trail.Id);
    }
}