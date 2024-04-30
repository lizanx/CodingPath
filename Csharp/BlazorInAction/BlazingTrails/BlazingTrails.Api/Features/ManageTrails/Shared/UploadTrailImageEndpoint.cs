using BlazingTrails.Shared.Features.ManageTrails.Shared;
using BlazingTrails.Shared.Features.ManageTrails.AddTrail;
using BlazingTrails.Api.Persistence;
using BlazingTrails.Api.Persistence.Entities;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Processing;

namespace BlazingTrails.Api.Features.ManageTrails.AddTrail;

public static class UploadTrailImageEndpoint
{
    public static async Task<IResult> UploadTrailImage(int trailId, HttpRequest request, BlazingTrailsContext db)
    {
        var trail = await db.Trails.SingleOrDefaultAsync(x => x.Id == trailId);
        if (trail == null)
        {
            return Results.BadRequest("Trail doesn't exist.");
        }

        var file = request.Form.Files[0];
        if (file == null || file.Length == 0)
        {
            return Results.BadRequest("No image found.");
        }

        var fileName = $"{Guid.NewGuid()}.jpg";
        var saveLocation = Path.Combine(Directory.GetCurrentDirectory(), "Images", fileName);

        var resizeOptions = new ResizeOptions()
        {
            Mode = ResizeMode.Pad,
            Size = new Size(640, 426)
        };

        using var image = Image.Load(file.OpenReadStream());
        image.Mutate(x => x.Resize(resizeOptions));
        await image.SaveAsJpegAsync(saveLocation);

        if (!string.IsNullOrWhiteSpace(trail.Image))
        {
            File.Delete(Path.Combine(Directory.GetCurrentDirectory(), "Images", trail.Image));
        }

        trail.Image = fileName;
        await db.SaveChangesAsync();

        return Results.Ok(trail.Image);
    }
}