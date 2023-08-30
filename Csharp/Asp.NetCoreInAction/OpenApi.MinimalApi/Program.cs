using System.Collections.Concurrent;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(opt =>
    opt.SwaggerDoc(
        "v1", new Microsoft.OpenApi.Models.OpenApiInfo()
        {
            Title = "Fruitify",
            Description = "An API for interacting with fruit stock",
            Version = "1.0"
        }
    )
);

var app = builder.Build();
app.UseSwagger();
app.UseSwaggerUI();

app.MapGet("/", () => "Hello World!");

// Fruit API
var _fruit = new ConcurrentDictionary<string, Fruit>();
app.MapGet("/fruit/{id}", (string id) =>
    _fruit.TryGetValue(id, out Fruit? fruit)
    ? TypedResults.Ok(fruit)
    : Results.Problem(statusCode: 404)
).WithTags("fruit")
.Produces<Fruit>()
.ProducesProblem(statusCode: 404);
app.MapPost("/fruit/{id}", (string id, Fruit fruit) =>
    _fruit.TryAdd(id, fruit)
    ? TypedResults.Created($"/fruit/{id}", fruit)
    : Results.ValidationProblem(
        new Dictionary<string, string[]>
        {
            { "id", new[] {"A fruit with this id already exists."} }
        }
    )
).WithTags("fruit")
.Produces<Fruit>(statusCode: 201)
.ProducesValidationProblem();

app.Run();

record Fruit(string Name, int Stock);