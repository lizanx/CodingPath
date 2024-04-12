using Microsoft.AspNetCore.Mvc;
using Data.Models;
using Data.Models.Interfaces;

namespace BlazorWebAssembly.Server.Endpoints
{
    public static class CategoryEndpoints
    {
        public static void MapCategoryApi(this WebApplication app)
        {
            app.MapGet("/api/Categories", async (IBlogApi api) =>
                Results.Ok(await api.GetCategoriesAsync()));
            app.MapGet("api/Categories/{*id}", async (IBlogApi api, string id) =>
                Results.Ok(await api.GetCategoryAsync(id)));

            app.MapPut("api/Categories", async (IBlogApi api, [FromBody] Category category) =>
                Results.Ok(await api.SaveCategoryAsync(category)))
                .RequireAuthorization();
            app.MapDelete("api/Categories/{*id}", async (IBlogApi api, string id) =>
                {
                    await api.DeleteTagAsync(id);
                    return Results.Ok();
                })
                .RequireAuthorization();
        }
    }
}
