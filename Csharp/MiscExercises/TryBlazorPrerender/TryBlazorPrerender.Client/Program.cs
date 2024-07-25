using Microsoft.AspNetCore.Components.WebAssembly.Hosting;
using TryBlazorPrerender.Client.Services;

var builder = WebAssemblyHostBuilder.CreateDefault(args);

builder.Services.AddSingleton<LanguageService>();

await builder.Build().RunAsync();
