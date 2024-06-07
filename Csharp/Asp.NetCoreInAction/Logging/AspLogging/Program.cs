using NetEscapades.Extensions.Logging.RollingFile;

var builder = WebApplication.CreateBuilder(args);

// Config host listening urls: this will override environment variables or cmd line parameters.
builder.WebHost.UseUrls("https://localhost:8081;http://*:8082");

// builder.Logging.AddJsonConsole();
builder.Logging.AddConsole();
builder.Logging.AddFile(options =>
{
    options.FileName = "Diagnostics-";
    options.Extension = "txt";
    options.LogDirectory = "LoggingFiles";
    options.Periodicity = PeriodicityOptions.Hourly;
});
builder.Logging.AddSeq();

// Add services to the container.
builder.Services.AddRazorPages();

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
