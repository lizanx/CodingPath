using System.Collections.Concurrent;
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

// app.MapGet("/", void () => throw new Exception("Test ExceptionHandler!")); // Test ProblemDetails in ExceptionHandler
// app.MapGet("/", () => Results.NotFound()); // Test ProblemDetails for error status code pages
app.MapGet("/", () => "Hello World!");
app.MapGet("/person/{name?}", (string? name) => $"Hello, {(name ?? "Mr. Anonymous")}!");

app.Run();

var _fruits = new ConcurrentDictionary<string, Fruit>()
{
    ["Apple"] = new("Apple", 10),
    ["Pear"] = new("Pear", 5),
    ["Peach"] = new("Peach", 3),
};
