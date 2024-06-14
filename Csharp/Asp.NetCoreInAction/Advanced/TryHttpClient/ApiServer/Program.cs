using Microsoft.AspNetCore.Mvc;
using SharedLib;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
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

var summaries = new[]
{
    "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
};

app.MapGet("/weatherforecast", async ([FromHeader] int WeatherForecastCount = 1) =>
{
    var forecast =  Enumerable.Range(1, WeatherForecastCount).Select(index =>
        new WeatherForecast
        (
            DateOnly.FromDateTime(DateTime.Now.AddDays(index)),
            Random.Shared.Next(-20, 55),
            summaries[Random.Shared.Next(summaries.Length)]
        ))
        .ToArray();
    
    await Task.Delay(100);
    return forecast;
})
.WithName("GetWeatherForecast")
.WithOpenApi();

var vehicles = new Vehicle[]
{
    new("Car", 100),
    new("Bicycle", 15),
    new("Train", 200),
    new("Plane", 350)
};
app.MapGet("/vehicle", async ([FromHeader] int vehicleCount, [FromHeader] string clientName) =>
{
    await Task.Delay(200);
    Console.WriteLine("Client Name: {0}", clientName);
    return Enumerable.Range(0, vehicleCount).Select(_ => vehicles[Random.Shared.Next(vehicles.Length)]);
});

app.Run();
