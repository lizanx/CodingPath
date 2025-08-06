using System.ComponentModel.DataAnnotations;
using Microsoft.Extensions.Options;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring OpenAPI at https://aka.ms/aspnet/openapi
builder.Services.AddOpenApi();

// Use Options pattern
var keySection = builder.Configuration.GetSection("AppKey");
// builder.Services.Configure<DevelopApiKeysOption>(keySection);
builder.Services.AddOptions<DevelopApiKeysOption>()
    .Bind(keySection)
    .ValidateDataAnnotations()
    .ValidateOnStart();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
}

app.UseHttpsRedirection();

app.MapGet("/", () => "Hello world!");

// Use IConfiguration
// app.MapGet("/Authorize", (IConfiguration configuration) => $"Key: {configuration["AppKey:Authorize"]}");
// app.MapGet("/Request", (IConfiguration configuration) => $"Key: {configuration["AppKey:Request"]}");

// Use Options pattern
app.MapGet("/Authorize", (IOptions<DevelopApiKeysOption> apiKeyOption) => $"Key: {apiKeyOption.Value.Authorize}");
app.MapGet("/Request", (IOptions<DevelopApiKeysOption> apiKeyOption) => $"Key: {apiKeyOption.Value.Request}");


app.Run();

class DevelopApiKeysOption
{
    [Required]
    public required string Authorize
    {
        get; set;
    }

    [Required]
    public required string Request
    {
        get; set;
    }
}

