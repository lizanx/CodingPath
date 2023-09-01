using Microsoft.EntityFrameworkCore;
using Cooking.Services;
using Cooking.Data;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddProblemDetails();
// Config EFCore
var connString = builder.Configuration.GetConnectionString("DefaultConnection");
builder.Services.AddDbContext<AppDbContext>(options =>
{
    options.UseSqlite(connString);
});
// Add RecipeService
builder.Services.AddScoped<RecipeService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

var routeGroup = app.MapGroup("")
    .WithTags("Recipe")
    .WithOpenApi();

routeGroup.MapGet("/", async (RecipeService service) =>
    await service.GetRecipes()
)
.WithSummary("List All Recipes");

routeGroup.MapGet("/{id}", async (int id, RecipeService service) =>
{
    var recipeViewModel = await service.GetRecipe(id);
    return recipeViewModel is null
        ? Results.NotFound()
        : Results.Ok(recipeViewModel);
})
.WithName("view-recipe")
.WithSummary("Get recipe")
.ProducesProblem(statusCode: 404)
.Produces<RecipeViewModel>();

routeGroup.MapPost("/", async (RecipeViewModel rvm, RecipeService service) =>
{
    int recipeId = await service.CreateRecipeAsync(rvm);
    return Results.Created("/", new{ recipeId });
})
.WithName("create-recipe")
.WithSummary("Create a new Recipe");

routeGroup.MapPut("/{id}", async (RecipeViewModel rvm, int id, RecipeService service) =>
{
    try
    {
        await service.UpdateRecipeAsync(rvm, id);
        return Results.NoContent();
    }
    catch (Exception e)
    {
        return Results.Problem($"Exception: {e}");
    }
})
.WithName("update-recipe")
.WithSummary("Update an old recipe")
.ProducesProblem(statusCode: 404);

routeGroup.MapDelete("/{id}", async (int id, RecipeService service) =>
{
    await service.DeleteRecipeAsync(id);
})
.WithDescription("delete-recipe")
.WithSummary("Delete an existed Recipe");

app.Run();
