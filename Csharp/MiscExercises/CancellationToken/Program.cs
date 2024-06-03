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
app.UseMiddleware<OperationCanceledMiddleware>();

app.MapGet("/no-cancel", async () =>
    {
        return await SlowTask("no-cancel", 10);
    });
app.MapGet("/cancel", async (CancellationToken token) =>
    {
        return await SlowTask("cancel", 10, token);
    });

app.Run();

static async Task<string> SlowTask(string taskName, int delayTime = 0, CancellationToken cancellationToken = default)
{
    Console.WriteLine("^Start executing {0}, delay = {1}", taskName, delayTime);
    await Task.Delay(delayTime * 1000, cancellationToken);
    Console.WriteLine("$Task {0} Finished", taskName);
    return taskName;
}

class OperationCanceledMiddleware
{
    private readonly RequestDelegate _next;
    
    private readonly ILogger<OperationCanceledMiddleware> _logger;

    public OperationCanceledMiddleware(RequestDelegate next, ILogger<OperationCanceledMiddleware> logger)
    {
        _next = next;
        _logger = logger;
    }

    public async Task Invoke(HttpContext context)
    {
        try
        {
            await _next(context);
        }
        catch (OperationCanceledException)
        {
            _logger.LogInformation("Request was cancelled");
            context.Response.StatusCode = 409;
        }
    }
}
