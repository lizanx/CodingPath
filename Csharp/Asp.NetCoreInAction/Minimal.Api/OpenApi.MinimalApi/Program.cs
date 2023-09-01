using System.Collections.Concurrent;

var builder = WebApplication.CreateBuilder(args);
if (builder.Environment.IsDevelopment())
{
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
}
var app = builder.Build();
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.MapGet("/", () => "Hello World!");

// Fruit API
var _fruit = new ConcurrentDictionary<string, Fruit>();
app.MapGet("/fruit/{id}", (string id) =>
    _fruit.TryGetValue(id, out Fruit? fruit)
    ? TypedResults.Ok(fruit)
    : Results.Problem(statusCode: 404)
).WithTags("fruit")
.Produces<Fruit>()
.ProducesProblem(statusCode: 404)
.WithSummary("Fetches a fruit")
.WithDescription("Fetches a fruit by id, or returns 404 if no fruit has the id.")
.WithOpenApi(op =>
{
    op.Parameters[0].Description = "The id of the fruit to fetch.";
    return op;
});
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
.ProducesValidationProblem()
// .WithSummary("Post a fruit")
// .WithDescription("Create a fruit with an id, or returns 400 if id already exists.")
.WithOpenApi(op =>
{
    op.Summary = "Post a fruit";
    op.Description = "Create a fruit with an id, or returns 400 if id already exists.";
    op.Parameters[0].Description = "The id of fruit to create.";
    return op;
});

app.Run();

record Fruit(string Name, int Stock);