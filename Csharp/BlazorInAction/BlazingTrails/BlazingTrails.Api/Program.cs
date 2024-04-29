using System.Reflection;
using BlazingTrails.Api.Persistence;
using FluentValidation.AspNetCore;
using FluentValidation;
using Microsoft.EntityFrameworkCore;
using BlazingTrails.Shared.Features.ManageTrails;
using Microsoft.AspNetCore.Mvc;
using BlazingTrails.Api.Persistence.Entities;
using Microsoft.AspNetCore.Http.HttpResults;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();

builder.Services.AddFluentValidationAutoValidation();
builder.Services.AddFluentValidationClientsideAdapters();
builder.Services.AddValidatorsFromAssembly(Assembly.Load("BlazingTrails.Shared"));

builder.Services.AddDbContext<BlazingTrailsContext>(options =>
    options.UseSqlite(builder.Configuration.GetConnectionString("BlazingTrailsContext")));

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseWebAssemblyDebugging();
}

app.UseHttpsRedirection();
app.UseBlazorFrameworkFiles();
app.UseStaticFiles();

app.UseRouting();

app.MapFallbackToFile("index.html");

app.MapPost(AddTrailRequest.RouteTemplate, async ([FromBody] AddTrailRequest request, BlazingTrailsContext db) =>
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
    });

app.Run();
