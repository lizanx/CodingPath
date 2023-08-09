using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Packt.Shared;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddRazorPages();
builder.Services.AddNorthwindContext();
builder.Services.AddRequestDecompression();
var app = builder.Build();

if (!app.Environment.IsDevelopment())
{
    app.UseHsts();
}
app.Use(
    async (HttpContext context, Func<Task> next) =>
    {
        RouteEndpoint? req = context.GetEndpoint() as RouteEndpoint;

        if (req is not null)
        {
            WriteLine($"Endpoint name: {req.DisplayName}");
            WriteLine($"Endpoint route pattern: {req.RoutePattern.RawText}");
        }

        if (context.Request.Path == "/bonjour")
        {
            await context.Response.WriteAsync("Bonjour Monde!");
            return;
        }

        await next();
    }
);
app.UseHttpsRedirection();
app.UseRequestDecompression();

app.UseDefaultFiles();
app.UseStaticFiles();

app.MapRazorPages();
app.MapGet("/hello", () => "Hello World!");

app.Run();

WriteLine("This executes after the web server has stopped!");
