using Microsoft.AspNetCore.Hosting.Server;
using Microsoft.AspNetCore.Hosting.Server.Features;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/", () => "Hello, this is a test project to retrieve url configs via IServer.");

app.MapGet(
    "/url-config",
    (IServer server) =>
        new
        {
            HostAddresses = server.Features.Get<IServerAddressesFeature>()?.Addresses,
            Platform = $"{Environment.OSVersion} - {Environment.Version}"
        }
);

app.Run();
