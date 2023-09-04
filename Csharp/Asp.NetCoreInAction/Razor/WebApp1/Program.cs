var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages()
.AddRazorPagesOptions(option =>
{
    // option.RootDirectory = ""; // Change the path of Pages folder
    option.Conventions.AddPageRoute("/Index", "/SecIndex"); // Add a new route for Index.cshtml, without replacing default routing.
});

// Customize the url: using lowercase + trailing slash
builder.Services.Configure<RouteOptions>(option =>
{
    option.LowercaseUrls = true;
    option.LowercaseQueryStrings = true;
    option.AppendTrailingSlash = true;
});

var app = builder.Build();

// Add StatusCodePagesMiddleware
app.UseStatusCodePagesWithReExecute("/Error");
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
