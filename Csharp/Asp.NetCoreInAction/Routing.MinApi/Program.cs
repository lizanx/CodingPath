using Microsoft.AspNetCore.Http.Json;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.Configure<RouteOptions>(opt =>
{
    opt.LowercaseUrls = true;
    opt.LowercaseQueryStrings = false;
    opt.AppendTrailingSlash = false;
});
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