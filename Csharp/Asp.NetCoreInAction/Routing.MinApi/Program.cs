using Microsoft.AspNetCore.Http.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using System.ComponentModel.DataAnnotations;

var builder = WebApplication.CreateBuilder(args);

// Test with configuration manager.
builder.Configuration.Sources.Clear();
builder.Configuration.AddJsonFile(
    "appsettings.json",
    optional: true,
    reloadOnChange: true);
// Test with user secrets.
builder.Configuration.AddUserSecrets<Program>();

builder.Services.Configure<RouteOptions>(opt =>
{
    opt.LowercaseUrls = true;
    opt.LowercaseQueryStrings = false;
    opt.AppendTrailingSlash = false;
});
// Test with IOption<T>
builder.Services.Configure<OptionTest>(builder.Configuration.GetSection(nameof(OptionTest)));
// Configure Json serialization/deserialization options.
builder.Services.ConfigureHttpJsonOptions((Microsoft.AspNetCore.Http.Json.JsonOptions option) =>
{
    option.SerializerOptions.AllowTrailingCommas = true;
    option.SerializerOptions.PropertyNameCaseInsensitive = true;
});

var app = builder.Build();

app.MapGet("/", () => "Hello World!");
app.MapGet("/Greeting/{name}", (string name) => $"Hello, {name}").WithName("greeting");
app.MapGet("/Greet/{name}", (string name, LinkGenerator links, HttpContext context) =>
{
    string? link = links.GetPathByName("greeting", new { name },
        options: new LinkOptions{ AppendTrailingSlash = true }); // This will override RouteOptions
    string? uri = links.GetUriByName(context, "greeting", new { name });
    return $"Go to greeting page at path: {link}\nUri: {uri}";
});
app.MapGet("/redirect", () =>
{
    return Results.RedirectToRoute("greeting", new{ name = "Mr. Anonymous" });
});

// Test module binding.
app.MapGet("/product/{p}", (Product p) => $"Product of id {p.Id}");

// Test array bingding in query strings.
app.MapGet("/array", ( [FromQuery(Name = "id")]int[] ids ) => $"Id count: {ids.Length}");

// Test customized BindAsync.
app.MapPost("/size", (SizeDetail size) => $"SizeDetail\nHeight: {size.Height}\nWidth: {size.Width}");

// Test AsParameter capsulation.
app.MapPost("/person/{id}",
    ([AsParameters]PersonInfo pi) => $"{pi.Id} | {pi.Person.Name} | {pi.Person.Age}");

// Test WithParameterValidation extension to add validation filter.
app.MapPost("/users/", (UserModel user) => $"User: Name={user.Name}, Email={user.Email}")
.WithParameterValidation();

// Test with configuration manager.
// app.MapGet("/settings", () => app.Configuration.AsEnumerable());
app.MapGet("/settings", (IConfiguration config) => config.AsEnumerable());
// Test with user secrets.
app.MapGet("/usersecrets", (IConfiguration config) => config.GetValue<string>("MapSettings:GoogleMapsApiKey"));

// Test with IOption<T>
app.MapGet("/ioption", (IOptions<OptionTest> iop) => iop.Value);

app.Run();

// A type implementing TryParse can be used for model binding.
readonly record struct Product(int Id)
{
    public static bool TryParse(string? input, out Product p)
    {
        if (input is not null
            && input.StartsWith('p')
            && int.TryParse(input.AsSpan()[1..], out int id))
        {
            p = new Product(id);
            return true;
        }
        p = default;
        return false;
    }
}

record SizeDetail(double Height, double Width)
{
    public static async ValueTask<SizeDetail?> BindAsync(HttpContext context)
    {
        using var sr = new StreamReader(context.Request.Body);
        string? line1 = await sr.ReadLineAsync(cancellationToken: context.RequestAborted);
        if (line1 is null) return null;
        string? line2 = await sr.ReadLineAsync(cancellationToken: context.RequestAborted);
        if (line2 is null) return null;
        return double.TryParse(line1, out double height)
            && double.TryParse(line2, out double width)
            ? new SizeDetail(height, width)
            : null;
    }
}

record Person(string Name, int Age);
record PersonInfo(int Id, [FromBody]Person Person);

record UserModel {
    [Required]
    [StringLength(10)]
    public string Name { get; set; } = null!;
    [Required]
    [EmailAddress]
    public string Email { get; set; } = null!;
}

// Test with IOption<T>
public class OptionTest
{
    public int IntValue { get; set; }
    public string StrValue { get; set; } = null!;
    public double DoubleValue { get; set; }
}