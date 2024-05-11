using Microsoft.EntityFrameworkCore;
using Microsoft.OpenApi.Models;
using PizzaStore.Data;
using PizzaStore.Models;

var builder = WebApplication.CreateBuilder(args);
string connectionString = builder.Configuration.GetConnectionString("Pizzas") ?? "Data Source=Pizzas.db";

builder.Services.AddSqlite<PizzaDb>(connectionString);
// builder.Services.AddDbContext<PizzaDb>(options =>
// {
//     options.UseInMemoryDatabase("items");
// });
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo{ Title = "PizzaStore API", Description = "Making the Pizzas you love", Version = "v1" });
});

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI(c =>
    {
        c.SwaggerEndpoint("/swagger/v1/swagger.json", "PizzaStore API v1");
    });
}

app.MapGet("/", () => "Hello World!");

app.MapGet("/pizzas", async (PizzaDb db) => await db.Pizzas.ToListAsync());
app.MapGet("/pizzas/{id}", async (int id, PizzaDb db) => await db.Pizzas.FindAsync(id));
app.MapPost("/pizzas", async (Pizza pizza, PizzaDb db) =>
{
    await db.Pizzas.AddAsync(pizza);
    await db.SaveChangesAsync();
    return Results.Created($"/pizzas/{pizza.Id}", pizza);
});
app.MapPut("/pizzas/{id}", async (int id, Pizza pizza, PizzaDb db) =>
{
    if ((await db.Pizzas.FindAsync(id)) is Pizza foundPizza)
    {
        foundPizza.Name = pizza.Name;
        foundPizza.Description = pizza.Description;
        await db.SaveChangesAsync();
        return Results.NoContent();
    }
    else
    {
        return Results.NotFound();
    }
});
app.MapDelete("/pizzas/{id}", async (int id, PizzaDb db) =>
{
    if ((await db.Pizzas.FindAsync(id)) is Pizza foundPizza)
    {
        db.Pizzas.Remove(foundPizza);
        await db.SaveChangesAsync();
        return Results.Ok();
    }

    return Results.NotFound();
});




app.Run();
