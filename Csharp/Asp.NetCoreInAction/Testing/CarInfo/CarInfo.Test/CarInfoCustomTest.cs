using CarInfo.Model;

namespace CarInfo.Test;

public class CarInfoCustomTest : IClassFixture<CarInfoWebApplicationFactory>
{
    private readonly CarInfoWebApplicationFactory _customFixture;

    public CarInfoCustomTest(CarInfoWebApplicationFactory customFixture)
    {
        _customFixture = customFixture;
    }

    [Fact]
    public async Task CarInfo_GetBmwCar()
    {
        HttpClient client = _customFixture.CreateClient();

        var response = await client.GetAsync("/4");

        response.EnsureSuccessStatusCode();
        Car car = await response.Content.ReadFromJsonAsync<Car>() ?? throw new Exception("Failed to get BMW car");
        Assert.Equal(4, car.Id);
        Assert.Equal("BMW", car.Brand);
        Assert.Equal("i5", car.Model);
    }
}