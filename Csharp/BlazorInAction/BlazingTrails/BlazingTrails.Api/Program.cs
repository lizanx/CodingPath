using System.Reflection;
using BlazingTrails.Api.Persistence;
using FluentValidation.AspNetCore;
using FluentValidation;
using Microsoft.EntityFrameworkCore;
using BlazingTrails.Shared.Features.ManageTrails.Shared;
using BlazingTrails.Shared.Features.ManageTrails.AddTrail;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using BlazingTrails.Api.Features.ManageTrails.AddTrail;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.Extensions.FileProviders;
using BlazingTrails.Api.Features.ManageTrails.EditTrail;
using BlazingTrails.Shared.Features.Home.Shared;
using BlazingTrails.Api.Features.Home.Shared;

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
app.UseStaticFiles(new StaticFileOptions()
    {
        FileProvider = new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(), @"Images")),
        RequestPath = new PathString("/Images")
    });

app.UseRouting();

app.MapFallbackToFile("index.html");

app.MapPost(AddTrailRequest.RouteTemplate, AddTrailEndpoint.AddTrail);
app.MapPost(UploadTrailImageRequest.RouteTemplate, UploadTrailImageEndpoint.UploadTrailImage)
    .DisableAntiforgery();
app.MapGet(GetTrailRequest.RouteTemplate, GetTrailEndpoint.GetTrail);
app.MapPut(EditTrailRequest.RouteTemplate, EditTrailEndpoint.EditTrail);
app.MapGet(GetTrailsRequest.RouteTemplate, GetTrailsEndpoint.GetTrails);

app.Run();
