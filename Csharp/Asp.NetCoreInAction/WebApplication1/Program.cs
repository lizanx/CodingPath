#if false
using Microsoft.AspNetCore.HttpLogging;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddHttpLogging(options =>
{
    options.LoggingFields = HttpLoggingFields.RequestProperties;
});
builder.Logging.AddFilter("Microsoft.AspNetCore.HttpLogging", LogLevel.Information);

var app = builder.Build();
if (app.Environment.IsDevelopment())
{
    LogInfo($"Content Root Path: {app.Environment.ContentRootPath}");
    LogInfo($"Web Root Path: {app.Environment.WebRootPath}");
    LogInfo($"Environment Name: {app.Environment.EnvironmentName}");
    LogInfo($"Application Name: {app.Environment.ApplicationName}");

    app.UseHttpLogging();
}

app.MapGet("/", () => "Nice to meet you, C# and ASP.NET!");
app.MapGet("/person", () => new Person("Gavin", "Xu"));

app.Run();

public record Person(string FirstName, string LastName);
#endif

// Simple middlewares.
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();
app.UseDeveloperExceptionPage();
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/error");
}
app.UseStaticFiles();
app.UseWelcomePage();
app.UseRouting();
app.MapGet("/", () => "Hello C#! Currently learning ASP.NET Core.");
app.MapGet("/error", () => "Sorry, an error occurred.");
app.Run();