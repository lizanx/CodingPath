using Microsoft.AspNetCore.ResponseCompression;
using Microsoft.EntityFrameworkCore;
using TaskManager.Server.Data;
using TaskManager.Shared;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();
builder.Services.AddRazorPages();
builder.Services.AddDbContext<TaskManagerServerDb>(options =>
    {
        options.UseSqlite(builder.Configuration.GetConnectionString("TaskManagerServerDb"));
    });

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseWebAssemblyDebugging();
}
else
{
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseBlazorFrameworkFiles();
app.UseStaticFiles();

app.UseRouting();

app.MapRazorPages();
app.MapControllers();
app.MapFallbackToFile("index.html");

// using (var scope = app.Services.CreateScope())
// {
//     var provider = scope.ServiceProvider;
//     var db = provider.GetRequiredService<TaskManagerServerDb>();
//     db?.TaskItems.Add(new TaskItem() { TaskName="Buy milk", IsCompleted = false });
//     db?.TaskItems.Add(new TaskItem() { TaskName="Read email", IsCompleted = false });
//     db?.SaveChanges();
// }

app.Run();
