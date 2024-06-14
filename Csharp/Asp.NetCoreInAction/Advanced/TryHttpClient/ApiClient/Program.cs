using ApiClient;
using Polly;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages();
builder.Services.AddHttpClient("weatherforecast", client =>
{
    client.BaseAddress = new Uri("https://localhost:7222/weatherforecast/");
    client.DefaultRequestHeaders.Add("WeatherForecastCount", "2");
});
builder.Services.AddHttpClient<VehicleClient>()
    .AddHttpMessageHandler<ClientNameMessageHandler>()
    .AddTransientHttpErrorPolicy(policy =>
        policy.WaitAndRetryAsync([
            TimeSpan.FromMilliseconds(100),
            TimeSpan.FromMilliseconds(200),
            TimeSpan.FromMilliseconds(500),
        ]));
builder.Services.AddTransient<ClientNameMessageHandler>();

builder.Services.AddSingleton<VehicleCacheService>();
builder.Services.AddHostedService<VehicleHostedService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapRazorPages();

app.Run();
