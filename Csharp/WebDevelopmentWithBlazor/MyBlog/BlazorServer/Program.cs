using BlazorServer.Data;
using Data;
using Data.Models.Interfaces;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using Auth0.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Components.RazorComponents;
using Components.Interfaces;
using BlazorServer.Services;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages();
builder.Services.AddServerSideBlazor();
builder.Services.AddSingleton<WeatherForecastService>();
builder.Services.AddOptions<BlogApiJsonDirectAccessSetting>()
    .Configure(options =>
    {
        options.DataPath = $@"..{Path.DirectorySeparatorChar}DataStorage";
        options.BlogPostsFolder = "Blogposts";
        options.CategoriesFolder = "Categories";
        options.TagsFolder = "Tags";
    });
builder.Services.AddScoped<IBlogApi, BlogApiJsonDirectAccess>();
builder.Services.AddAuth0WebAppAuthentication(
    options =>
    {
        options.Domain = builder.Configuration["Auth0:Authority"] ?? "";
        options.ClientId = builder.Configuration["Auth0:ClientId"] ?? "";
    });
builder.Services.AddTransient<ILoginStatus, LoginStatus>();
builder.Services.AddScoped<IBrowserStorage, BlogProtectedBrowserStorage>();
builder.Services.AddSingleton<IBlogNotificationService, BlazorServerBlogNotificationService>();

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

app.UseAuthentication();
app.UseAuthorization();

app.MapBlazorHub();
app.MapFallbackToPage("/_Host");

app.MapGet("authentication/login", async (string redirectUri, HttpContext context) =>
{
    var authenticationProperties = new LoginAuthenticationPropertiesBuilder().WithRedirectUri(redirectUri).Build();
    await context.ChallengeAsync(Auth0Constants.AuthenticationScheme, authenticationProperties);
});
app.MapGet("authentication/logout", async (HttpContext context) =>
{
    var authenticationProperties = new LogoutAuthenticationPropertiesBuilder().WithRedirectUri("/").Build();
    await context.SignOutAsync(Auth0Constants.AuthenticationScheme, authenticationProperties);
    await context.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
});
app.Run();
