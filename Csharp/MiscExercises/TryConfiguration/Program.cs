using Microsoft.Extensions.Options;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring OpenAPI at https://aka.ms/aspnet/openapi
builder.Services.AddOpenApi();

// Configuration
builder.Services.Configure<User>(builder.Configuration.GetSection("User"));

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
}

app.UseHttpsRedirection();

app.MapGet("/user/name", (IConfiguration config) =>
{
    string userName = config["User:Name"] ?? "Unknown";
    return userName;
});

app.MapGet("/user/age", (IConfiguration config) =>
{
    int age = config.GetValue("User:Age", 20);
    return age;
});

app.MapGet("/user/career", (IConfiguration config) =>
{
    var career = config.GetSection("User:Career").Get<Career>() ?? new Career { Title = "Unknown", Location = "Unknown" };
    return career;
});

// Won't detect change at runtime
app.MapGet("/user1", (IOptions<User> user) =>
{
    return user;
});

// Will detect change at runtime
app.MapGet("/user2", (IOptionsSnapshot<User> user) =>
{
    return user;
});

app.Run();

internal class Career
{
    public string Title { get; set; } = String.Empty;

    public string Location { get; set; } = string.Empty;
}

internal class User
{
    public string Name { get; set; } = string.Empty;

    public int Age { get; set; } = default;

    public Career Career { get; set; } = new Career();
}
