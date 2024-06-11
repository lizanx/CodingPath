var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowSiblingSite", policyBuilder =>
    {
        policyBuilder.AllowAnyMethod();
        policyBuilder.WithOrigins("https://localhost:7123");
    });
});

var app = builder.Build();

app.UseRouting();
app.UseCors();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/person", () => new Person("Gavin", 22)).RequireCors("AllowSiblingSite");

app.Run();

record Person(string Name, int Age);
