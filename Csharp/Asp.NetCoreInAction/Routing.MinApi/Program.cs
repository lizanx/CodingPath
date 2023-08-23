
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", () => "Hello World!");
app.MapGet("/greeting/{name}", (string name) => $"Hello, {name}").WithName("greeting");
app.MapGet("/greet/{name}", (string name, LinkGenerator links, HttpContext context) =>
{
    string? link = links.GetPathByName("greeting", new { name });
    string? uri = links.GetUriByName(context, "greeting", new { name });
    return $"Go to greeting page at path: {link}\nUri: {uri}";
});

app.Run();
