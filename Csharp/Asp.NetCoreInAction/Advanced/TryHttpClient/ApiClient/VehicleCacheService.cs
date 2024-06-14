using SharedLib;

namespace ApiClient;

public class VehicleCacheService
{
    public IEnumerable<Vehicle> Vehicles { get; private set; } = [];

    public void SetCache(IEnumerable<Vehicle> vehicles)
    {
        Vehicles = vehicles;
    }
}
