using CarInfo.Model;
using CarInfo.Persistence;
using CarInfo.Service;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddDbContext<CarDbContext>(options =>
    options.UseSqlite(builder.Configuration.GetConnectionString("Sqlite")));
builder.Services.AddScoped<ICarService, CarService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/", (ICarService service) => service.GetCars());
app.MapGet("/{id:int}", (int id, ICarService service) => service.GetCarAsync(id));
app.MapPost("/", async (ICarService service, Car car) =>
    {
        await service.CreateCarAsync(car);
        return Results.Created();
    });
app.MapDelete("/{id:int}", async (ICarService service, int id) =>
    {
        await service.RemoveCarAsync(id);
        return Results.NoContent();
    });

app.Run();

public partial class Program {}
