using Microsoft.AspNetCore.Http.HttpResults; // Results
using Microsoft.AspNetCore.Mvc; // [FromServices]
using Packt.Shared; // AddNorthwindContext

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddNorthwindContext();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/", () => "Hello World!");

int pageSize = 10;

// app.MapGet("/api/products", (
//     [FromServices] NorthwindContext db,
//     [FromQuery] int? page) =>
//     db.Products.Where(p => 
//         p.UnitsInStock > 0 && !p.Discontinued)
//         .Skip(((page ?? 1) - 1) * pageSize)
//         .Take(pageSize)
//     )
//     .WithName("");

app.Run();
