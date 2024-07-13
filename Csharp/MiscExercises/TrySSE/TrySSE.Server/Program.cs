using System.Text.Json;
using Microsoft.Net.Http.Headers;
using TrySSE.Shared;

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

Car[] cars = [
    new("BMW", 350_000),
    new("Zeekr", 29_000),
    new("NIO", 33_000),
];

string[] eventTypes = ["Car", "WeatherForecast"];

app.MapGet("/sse", async (HttpContext context) =>
{
    context.Response.Headers.Append(HeaderNames.ContentType, "text/event-stream");

    while (!context.RequestAborted.IsCancellationRequested)
    {
        var eventType = eventTypes[Random.Shared.Next(eventTypes.Length)];

        await context.Response.WriteAsync($"event: {eventType}\n");
        await context.Response.WriteAsync("data: ");
        switch (eventType)
        {
            case "Car":
                await JsonSerializer.SerializeAsync(context.Response.Body, cars[Random.Shared.Next(cars.Length)]);
                break;
            case "WeatherForecast":
                var forecast = new WeatherForecast(
                    DateOnly.FromDateTime(DateTime.Now.AddDays(Random.Shared.Next(0, 8))),
                    Random.Shared.Next(-40, 50),
                    summaries[Random.Shared.Next(summaries.Length)]
                );
                await JsonSerializer.SerializeAsync(context.Response.Body, forecast);
                break;
            default:
                throw new InvalidOperationException($"Unknown event type {eventType}");
        }
        await context.Response.WriteAsync("\n\n");
        await context.Response.Body.FlushAsync();

        await Task.Delay(2000);
    }
});

app.Run();
