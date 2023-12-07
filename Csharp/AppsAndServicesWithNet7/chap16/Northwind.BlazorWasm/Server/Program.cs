using Microsoft.AspNetCore.ResponseCompression;
using Microsoft.AspNetCore.Mvc; // [FromServices]
using System.Text.Json.Serialization; // ReferenceHandler
using Packt.Shared;

// Define an alias for the JsonOptions class
using HttpJsonOptions = Microsoft.AspNetCore.Http.Json.JsonOptions;

var builder = WebApplication.CreateBuilder(args);

builder.Services.Configure<HttpJsonOptions>(options =>
    {
        // Handle circular references between employees and managers.
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

app.MapGet("api/employees",
    ([FromServices] NorthwindContext db) => Results.Json(db.Employees))
    .WithName("GetEmployees")
    .Produces<Employee[]>(StatusCodes.Status200OK);

app.MapGet("api/employees/{id:int}",
    ([FromServices] NorthwindContext db, [FromRoute] int id) =>
        {
            Employee? e = db.Employees.Find(id);
            return e is null ? Results.NotFound() : Results.Json(e);
        })
    .WithName("GetEmployeesById")
    .Produces<Employee>(StatusCodes.Status200OK)
    .Produces(StatusCodes.Status404NotFound);

app.MapGet("api/employees/{country}",
    ([FromServices] NorthwindContext db, [FromRoute] string country) =>
        Results.Json(db.Employees.Where(e => e.Country == country)))
    .WithName("GetEmployeesByCountry")
    .Produces<Employee[]>(StatusCodes.Status200OK);

app.MapPost("api/employees",
    async ([FromServices] NorthwindContext db, [FromBody] Employee employee) =>
        {
            db.Employees.Add(employee);
            await db.SaveChangesAsync();
            return Results.Created($"api/employees/{employee.EmployeeId}", employee);
        })
    .Produces<Employee>(StatusCodes.Status201Created);

app.MapRazorPages();
app.MapControllers();
app.MapFallbackToFile("index.html");

app.Run();
