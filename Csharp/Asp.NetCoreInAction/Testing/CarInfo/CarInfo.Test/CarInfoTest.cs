using CarInfo.Model;
using CarInfo.Service;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.DependencyInjection.Extensions;

namespace CarInfo.Test;

public class CarInfoTest : IClassFixture<WebApplicationFactory<Program>>
{
    private readonly WebApplicationFactory<Program> _fixture;

    public CarInfoTest(WebApplicationFactory<Program> fixture)
    {
        _fixture = fixture;
    }

    [Fact]
    public async Task CarInfo_GetNioCar()
    {
        var customFactory = _fixture.WithWebHostBuilder(webHost =>
            {
                webHost.ConfigureServices(services =>
                    {
                        services.RemoveAll<ICarService>();
                        services.AddScoped<ICarService, StubCarService>();
                    });
            });
        HttpClient client = customFactory.CreateClient();

        var response = await client.GetAsync("/2");

        response.EnsureSuccessStatusCode();
        Car car = await response.Content.ReadFromJsonAsync<Car>() ?? throw new Exception("Failed to get NIO car");
        Assert.Equal(2, car.Id);
        Assert.Equal("NIO", car.Brand);
        Assert.Equal("ET5", car.Model);
    }
}