using System.Net.Mime;
using CustomMiddleware;

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

app.Use(async (context, next) =>
{
    context.Response.OnStarting(() => 
    {
        context.Response.Headers["My-Custom-Header"] = "Middleware via Use + lambda";
        return Task.CompletedTask;
    });
    await next(context);
});

app.Map("/branch", (IApplicationBuilder app) =>
{
    app.UsePingPong();
});

// app.UsePingPong();

app.MapGet("/weatherforecast", () =>
{
    var summaries = new[]
    {
        "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
    };

    var forecast =  Enumerable.Range(1, 5).Select(index =>
        new WeatherForecast
        (
            DateOnly.FromDateTime(DateTime.Now.AddDays(index)),
            Random.Shared.Next(-20, 55),
            summaries[Random.Shared.Next(summaries.Length)]
        ))
        .ToArray();
    return forecast;
})
.WithName("GetWeatherForecast")
.WithOpenApi();

// If you add middleware using IApplicationBuilder.Run(lambda),
// the weatherforecast endpoint won't get executed since endpoint middleware can't be reached.
// app.Run(async (HttpContext context) =>
// {
//     context.Response.ContentType = "text/plain";
//     await context.Response.WriteAsync("Hello! Written by middleware in Run()!");
// });

app.Run();

record WeatherForecast(DateOnly Date, int TemperatureC, string? Summary)
{
    public int TemperatureF => 32 + (int)(TemperatureC / 0.5556);
}
