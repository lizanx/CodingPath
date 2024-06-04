using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using RazorIdentity.Auth.Handler;
using RazorIdentity.Auth.Requirement;
using RazorIdentity.Data;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
var connectionString = builder.Configuration.GetConnectionString("DefaultConnection") ?? throw new InvalidOperationException("Connection string 'DefaultConnection' not found.");
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlite(connectionString));
builder.Services.AddDatabaseDeveloperPageExceptionFilter();

builder.Services.AddAuthorization(options =>
    {
        options.AddPolicy("HasName", policy => policy.RequireClaim("FullName"));
        options.AddPolicy("NameLength>4", policy => policy.AddRequirements(new NameLengthRequirement(5)));
        options.AddPolicy("Gmail", policy => policy.AddRequirements(new EmailProviderRequirement("gmail")));
        options.AddPolicy("Outlook", policy => policy.AddRequirements(new EmailProviderRequirement("outlook")));
    });
builder.Services.AddSingleton<IAuthorizationHandler, NameLengthHandler>();
builder.Services.AddScoped<IAuthorizationHandler, EmailProviderHandler>();

builder.Services.AddDefaultIdentity<IdentityUser>(options => 
    {
        options.SignIn.RequireConfirmedAccount = false;
        options.Lockout.AllowedForNewUsers = true;
        options.Password.RequiredLength = 3;
        options.Password.RequireDigit = false;
        options.Password.RequireNonAlphanumeric = false;
        options.Password.RequireLowercase = false;
        options.Password.RequireUppercase = false;
    })
    .AddEntityFrameworkStores<ApplicationDbContext>();

builder.Services.AddRazorPages();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseMigrationsEndPoint();
}
else
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

app.MapRazorPages();

app.Run();
