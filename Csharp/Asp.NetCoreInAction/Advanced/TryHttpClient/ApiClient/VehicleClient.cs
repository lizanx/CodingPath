using SharedLib;

namespace ApiClient;

public class VehicleClient
{
    private readonly HttpClient _client;

    public VehicleClient(HttpClient client)
    {
        _client = client;
        _client.BaseAddress = new Uri("https://localhost:7222/vehicle/");
    }

    public async Task<IEnumerable<Vehicle>> GetVehiclesAsync(int count = 2)
    {
        _client.DefaultRequestHeaders.Add("VehicleCount", count.ToString());

        var vehicles = await _client.GetFromJsonAsync<IEnumerable<Vehicle>>("")
            ?? throw new InvalidOperationException("Failed to get vehicles from server");

        return vehicles;
    }
}
