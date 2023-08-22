using System.Collections.Concurrent;
using System.Net.Mime;
using System.Reflection;
using MinimalApi.Data;
using static HelperUtils.ColoredLog;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddProblemDetails();

var app = builder.Build();
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler();
}
app.UseStatusCodePages();

// Test with fruits.
var _fruits = new ConcurrentDictionary<string, Fruit>()
{
    ["Apple"] = new("Apple", 10),
    ["Pear"] = new("Pear", 5),
    ["Peach"] = new("Peach", 3),
};
app.MapGet("/fruit", () => _fruits);
app.MapGet("/fruit/{id}", (string id) =>
    _fruits.TryGetValue(id, out Fruit? fruit) ? TypedResults.Ok(fruit) : Results.NotFound()
)
// .AddEndpointFilter(ValidationHelper.ValidateId)
.AddEndpointFilter<IdValidationFilter>() // This is the same as above call.
.AddEndpointFilter( async (context, next) =>
// This filter is behind ValidateId, thus won't be executed if ValidateId short-curcuits the pipeline.
{
    app.Logger.LogInformation("Executing lambda filter...");
    object? result = await next(context);
    app.Logger.LogInformation("Handler result: {result}", result);
    return result;
});
app.MapPost("/fruit/{id}", (string id, Fruit fruit) =>
    _fruits.TryAdd(id, fruit) ? TypedResults.Created($"/fruit/{id}")
        : Results.BadRequest(new { id = "A fruit with this id already exists."})
);
app.MapPut("/fruit/{id}", (string id, Fruit fruit) =>
{
    _fruits[id] = fruit;
    return Results.NoContent();
});
app.MapDelete("/fruit/{id}", (string id) =>
{
    _fruits.TryRemove(id, out _);
    return Results.NoContent();
});

// Test with HttpResponse Handler
app.MapGet("/teapot", (HttpResponse response) =>
{
    response.StatusCode = 200;
    response.ContentType = MediaTypeNames.Text.Plain;
    return response.WriteAsync("You're requesting Teapot!");
});

// Test EndpointFilterFacotry with person endpoint.
// Now only people whose name starts with 'M' will be greeted.
app.MapGet("/person/{name}", (string name) => $"Hello, {name}!")
.AddEndpointFilterFactory(ValidationHelper.ValidateName);

// app.MapGet("/", void () => throw new Exception("Test ExceptionHandler!")); // Test ProblemDetails in ExceptionHandler
// app.MapGet("/", () => Results.NotFound()); // Test ProblemDetails for error status code pages
app.MapGet("/", () => "Hello World!");

app.Run();


// Endpoint Filter
class ValidationHelper
{
    internal static async ValueTask<Object?> ValidateId(
        EndpointFilterInvocationContext context,
        EndpointFilterDelegate next)
    {
        var id = context.GetArgument<string>(0);
        if (string.IsNullOrEmpty(id) || !id.StartsWith('P'))
        {
            return Results.ValidationProblem(new Dictionary<string, string[]>()
            {
                { "id", new[] {"Invalid format, id must start with 'P'."} }
            });
        }
        return await next(context);
    }

    internal static EndpointFilterDelegate ValidateName(
        EndpointFilterFactoryContext context,
        EndpointFilterDelegate next)
    {
        int? namePosition = default;
        ParameterInfo[] parameters = context.MethodInfo.GetParameters();
        for (int i = 0; i < parameters.Length; i++)
        {
            if (parameters[i].Name == "name" && parameters[i].ParameterType == typeof(string))
            {
                namePosition = i;
            }
        }

        if (!namePosition.HasValue)
        {
            return next;
        }

        return async (invocationContext) =>
        {
            string name = invocationContext.GetArgument<string>(namePosition.Value);
            if (string.IsNullOrEmpty(name) || !name.StartsWith('M'))
            {
                return Results.ValidationProblem(new Dictionary<string, string[]>()
                {
                    { "id", new[] { "name must start with 'M'!"} }
                });
            }

            return await next(invocationContext);
        };
    }
}

// IEndpointFilter for AddEndpointFilter
class IdValidationFilter : IEndpointFilter
{
    public async ValueTask<object?> InvokeAsync(
        EndpointFilterInvocationContext context,
        EndpointFilterDelegate next)
    {
        string? id = context.GetArgument<string>(0);
        if (string.IsNullOrEmpty(id) || !id.StartsWith('P'))
        {
            return Results.ValidationProblem(new Dictionary<string, string[]>()
            {
                { "id", new[] { "Invalid id, must start with 'P'."}}
            });
        }
        return await next(context);
    }
}