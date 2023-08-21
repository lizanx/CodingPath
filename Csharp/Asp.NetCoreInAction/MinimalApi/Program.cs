using System.Collections.Concurrent;
using System.Net.Mime;
using MinimalApi.Data;
using static HelperUtils.ColoredLog;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddProblemDetails();

var app = builder.Build();
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler();
}
app.UseStatusCodePages();

// Test with fruits.
var _fruits = new ConcurrentDictionary<string, Fruit>()
{
    ["Apple"] = new("Apple", 10),
    ["Pear"] = new("Pear", 5),
    ["Peach"] = new("Peach", 3),
};
app.MapGet("/fruit", () => _fruits);
app.MapGet("/fruit/{id}", (string id) =>
    _fruits.TryGetValue(id, out Fruit? fruit) ? TypedResults.Ok(fruit) : Results.NotFound()
);
app.MapPost("/fruit/{id}", (string id, Fruit fruit) =>
    _fruits.TryAdd(id, fruit) ? TypedResults.Created($"/fruit/{id}")
        : Results.BadRequest(new { id = "A fruit with this id already exists."})
);
app.MapPut("/fruit/{id}", (string id, Fruit fruit) =>
{
    _fruits[id] = fruit;
    return Results.NoContent();
});
app.MapDelete("/fruit/{id}", (string id) =>
{
    _fruits.TryRemove(id, out _);
    return Results.NoContent();
});

// Test with HttpResponse Handler
app.MapGet("/teapot", (HttpResponse response) =>
{
    response.StatusCode = 200;
    response.ContentType = MediaTypeNames.Text.Plain;
    return response.WriteAsync("You're requesting Teapot!");
});

// app.MapGet("/", void () => throw new Exception("Test ExceptionHandler!")); // Test ProblemDetails in ExceptionHandler
// app.MapGet("/", () => Results.NotFound()); // Test ProblemDetails for error status code pages
app.MapGet("/", () => "Hello World!");
app.MapGet("/person/{name?}", (string? name) => $"Hello, {(name ?? "Mr. Anonymous")}!");

app.Run();

