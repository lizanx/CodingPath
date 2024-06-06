using NetEscapades.Extensions.Logging.RollingFile;

var builder = WebApplication.CreateBuilder(args);

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
