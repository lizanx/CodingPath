using DemoWebApi.Filters;

var builder = WebApplication.CreateBuilder(args);
builder.Logging.AddFile();
builder.Logging.AddSeq();

// Add services to the container.

builder.Services.AddControllers(options =>
{
    // options.Filters.Add<LogResourceFilter>(); // Add Global-Scope filter.
    options.Filters.Add(new LogResourceFilter(1)); // Equivalent call.
    // options.Filters.Add(typeof(LogResourceFilter)); // Equivalent call.
});
    // .AddXmlSerializerFormatters();
    // Modify the default behavior of [ApiController].
    // .ConfigureApiBehaviorOptions(options =>
    // {
    //     options.SuppressModelStateInvalidFilter = true;
    // });

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

app.UseAuthorization();

app.MapControllers();

app.Run();
