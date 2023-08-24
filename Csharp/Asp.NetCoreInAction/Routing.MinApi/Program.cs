
var builder = WebApplication.CreateBuilder(args);
builder.Services.Configure<RouteOptions>(opt =>
{
    opt.LowercaseUrls = true;
    opt.LowercaseQueryStrings = false;
    opt.AppendTrailingSlash = false;
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