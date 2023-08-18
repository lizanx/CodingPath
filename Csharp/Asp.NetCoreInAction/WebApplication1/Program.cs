var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", () => "Nice to meet you, C# and ASP.NET!");

app.Run();
