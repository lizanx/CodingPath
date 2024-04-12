using Data.Models.Interfaces;
using Data;
using Microsoft.AspNetCore.ResponseCompression;
using BlazorWebAssembly.Server.Endpoints;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllersWithViews();
builder.Services.AddRazorPages();
builder.Services.AddOptions<BlogApiJsonDirectAccessSetting>()
    .Configure(options =>
    {
        //options.DataPath = $@"..{Path.DirectorySeparatorChar}..DataStorage";
        options.DataPath = Path.Join(Directory.GetCurrentDirectory(), "..", "..", "DataStorage");
        options.BlogPostsFolder = "Blogposts";
        options.CategoriesFolder = "Categories";
        options.TagsFolder = "Tags";
        Console.WriteLine($"Data path: {Path.GetFullPath(options.DataPath)}");
    });
builder.Services.AddScoped<IBlogApi, BlogApiJsonDirectAccess>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseWebAssemblyDebugging();
}
else
{
    app.UseExceptionHandler("/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();

app.UseBlazorFrameworkFiles();
app.UseStaticFiles();

app.UseRouting();

app.MapBlogPostApi();
app.MapCategoryApi();
app.MapTagApi();

app.MapRazorPages();
app.MapControllers();
app.MapFallbackToFile("index.html");

app.Run();
