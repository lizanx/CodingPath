using BlazingTrails.Api.Persistence;
using BlazingTrails.Shared.Features.Home.Shared;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BlazingTrails.Api.Features.Home.Shared;

public static class GetTrailsEndpoint
{
    public static async Task<IResult> GetTrails([FromBody] GetTrailsRequest request, BlazingTrailsContext db, CancellationToken cancellationToken = default)
    {
        Console.WriteLine("GetTrails");
        var trails = await db.Trails
            .Include(t => t.Route)
            .ToListAsync(cancellationToken);
        
        var response = new GetTrailsRequest.Response(trails.Select(t =>
            new GetTrailsRequest.Trail(t.Id, t.Name, t.Image, t.Location, t.TimeInMinutes, t.Length, t.Description)));
        Console.WriteLine("Get Trails: count = {0}", response?.Trails.Count() ?? -1);
        return Results.Ok(response);
    }
}
