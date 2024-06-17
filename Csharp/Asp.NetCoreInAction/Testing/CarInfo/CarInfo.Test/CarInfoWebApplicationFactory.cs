using CarInfo.Service;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.DependencyInjection.Extensions;

namespace CarInfo.Test;

public class CarInfoWebApplicationFactory : WebApplicationFactory<Program>
{
    protected override void ConfigureWebHost(IWebHostBuilder builder)
    {
        builder.ConfigureServices(services =>
            {
                services.RemoveAll<ICarService>();
                services.AddScoped<ICarService, StubCarService>();
            });
    }
}
