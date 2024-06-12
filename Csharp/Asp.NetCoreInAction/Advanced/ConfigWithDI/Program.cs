using ConfigWithDI;
using ConfigWithDI.Services;
using Microsoft.Extensions.Options;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// 1st method
// builder.Services.Configure<GuidConfig>(builder.Configuration.GetSection("GuidConfig"));
// builder.Services.Configure<GuidConfig>(config =>
//     config.Guids = Enumerable.Range(0, config.Count).Select(_ => Guid.NewGuid()));

// 2nd method
// builder.Services.AddOptions<GuidConfig>()
//     .BindConfiguration("GuidConfig")
//     .Configure(config => config.Guids = Enumerable.Range(0, config.Count).Select(_ => Guid.NewGuid()));

// 3rd method: DI with singleton service
// builder.Services.AddOptions<GuidConfig>()
//     .BindConfiguration("GuidConfig")
//     .Configure<IGuidService>((config, service) =>
//         {
//             config.Guids = service.GetGuids(config.Count);
//         });
// Cannot use scoped service here:
// System.InvalidOperationException: Cannot resolve scoped service 'ConfigWithDI.Services.IGuidService' from root provider.
// builder.Services.AddSingleton<IGuidService, SingletonGuidService>();

// 4th method: DI with scoped service
// builder.Services.AddOptions<GuidConfig>()
//     .BindConfiguration("GuidConfig")
//     .Configure<IServiceProvider>((config, serviceProvider) =>
//         {
//             using var scope = serviceProvider.CreateScope();
//             var guidService = scope.ServiceProvider.GetRequiredService<IGuidService>();
//             config.Guids = guidService.GetGuids(config.Count);
//         });
// builder.Services.AddScoped<IGuidService, ScopeGuidService>();

// 5th method: DI with scoped service, using IConfigurationOptions<T>
builder.Services.Configure<GuidConfig>(builder.Configuration.GetSection("GuidConfig"));
builder.Services.AddSingleton<IConfigureOptions<GuidConfig>, ConfigureGuidOptions>();
builder.Services.AddScoped<IGuidService, ScopeGuidService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.MapGet("/", (IOptions<GuidConfig> config) => config.Value);

app.Run();

class GuidConfig
{
    public string Name { get; set; } = string.Empty;
    public int Count { get; set; }
    public IEnumerable<Guid> Guids { get; set; } = [];
}
