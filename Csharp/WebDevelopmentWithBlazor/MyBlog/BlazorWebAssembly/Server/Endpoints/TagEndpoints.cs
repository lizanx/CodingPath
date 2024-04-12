using Microsoft.AspNetCore.Mvc;
using Data.Models;
using Data.Models.Interfaces;

namespace BlazorWebAssembly.Server.Endpoints
{
    public static class TagEndpoints
    {
        public static void MapTagApi(this WebApplication app)
        {
            app.MapGet("api/Tags", async (IBlogApi api) =>
                Results.Ok(await api.GetTagsAsync()));
            app.MapGet("api/Tags/{*id}", async (IBlogApi api, string id) =>
                Results.Ok(await api.GetTagAsync(id)));

            app.MapPut("api/Tags", async (IBlogApi api, [FromBody] Tag tag) =>
                Results.Ok(await api.SaveTagAsync(tag)))
                .RequireAuthorization();
            app.MapDelete("api/Tags/{*id}", async (IBlogApi api, string id) =>
                {
                    await api.DeleteTagAsync(id);
                    return Results.Ok();
                })
                .RequireAuthorization();
        }
    }
}
