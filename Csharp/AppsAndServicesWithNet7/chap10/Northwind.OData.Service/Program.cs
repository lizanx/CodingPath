using Microsoft.AspNetCore.OData; // AddOData
using Packt.Shared;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddNorthwindContext();

builder.Services.AddControllers()
    .AddOData(options =>
        options
        .AddRouteComponents(routePrefix: "catalog",
            model: GetEdmModelForCatalog())
        .AddRouteComponents(routePrefix: "ordersystem",
            model: GetEdmModelForOrderSystem())
        .AddRouteComponents(routePrefix: "catalog/v{version}",
            model: GetEdmModelForCatalog())
        .Select() // enable $select for projection
        .Expand() // enable $expand to navigate to related entities
        .Filter() // enbale $filter
        .OrderBy() // enable $orderby
        .SetMaxTop(100) // enable $top
        .Count() // enable $count
    );

// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();
