using Microsoft.EntityFrameworkCore;
using Cooking.Services;
using Cooking.Data;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
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

app.MapGet("/recipe/{id}", async (int id, RecipeService service) =>
{
    var recipe = await service.GetRecipe(id);
    return recipe is null
        ? Results.NotFound()
        : Results.Ok(recipe);
})
.WithName("view-recipe")
.WithSummary("Get recipe")
.ProducesProblem(statusCode: 404)
.Produces<Recipe>();

app.MapPost("/recipe", async ([FromBody]Recipe recipe, RecipeService service) =>
{
    int recipeId = await service.CreateRecipeAsync(recipe);
    return Results.CreatedAtRoute("view-recipe", new { recipeId });
});

app.Run();
