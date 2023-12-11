using Microsoft.AspNetCore.ResponseCompression;
using Microsoft.AspNetCore.Mvc; // [FromServices]
using System.Text.Json.Serialization; // ReferenceHandler
using Microsoft.EntityFrameworkCore;
using Packt.Shared;

using HttpJsonOptions = Microsoft.AspNetCore.Http.Json.JsonOptions;
using System.Net;

var builder = WebApplication.CreateBuilder(args);

builder.Services.Configure<HttpJsonOptions>(options =>
    {
        options.SerializerOptions.ReferenceHandler = ReferenceHandler.Preserve;
    });

builder.Services.AddControllersWithViews();
builder.Services.AddRazorPages();
builder.Services.AddNorthwindContext();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseWebAssemblyDebugging();
}
else
{
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseBlazorFrameworkFiles();
app.UseStaticFiles();

app.UseRouting();

app.MapGet("api/categories", ([FromServices] NorthwindContext db) =>
        Results.Json(
            db.Categories.Include(category => category.Products)
        )
    )
    .WithName("GetCategories")
    .Produces<Category[]>(StatusCodes.Status200OK);

app.MapGet("api/orders/", ([FromServices] NorthwindContext db) =>
        Results.Json(db.Orders.Include(order => order.OrderDetails))
    )
    .WithName("GetOrders")
    .Produces<Order[]>(StatusCodes.Status200OK);

app.MapRazorPages();
app.MapControllers();
app.MapFallbackToFile("index.html");

app.Run();
