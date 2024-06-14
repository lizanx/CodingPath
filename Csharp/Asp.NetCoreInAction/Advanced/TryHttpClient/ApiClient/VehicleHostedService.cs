using SharedLib;

namespace ApiClient;

public class VehicleHostedService : BackgroundService
{
    private IEnumerable<Vehicle> _vehicles = [];
    private readonly IServiceProvider _serviceProvider;
    private readonly VehicleCacheService _vehicleCacheService;

    public VehicleHostedService(IServiceProvider serviceProvider, VehicleCacheService vehicleCacheService)
    {
        _serviceProvider = serviceProvider;
        _vehicleCacheService = vehicleCacheService;
    }

    public override async Task StartAsync(CancellationToken cancellationToken)
    {
        while (!cancellationToken.IsCancellationRequested && !_vehicles.Any())
        {
            var client = _serviceProvider.GetRequiredService<VehicleClient>()
                ?? throw new InvalidOperationException("Failed to get VehicleClient");
            
            _vehicles = await client.GetVehiclesAsync(3);

            _vehicleCacheService.SetCache(_vehicles);
        }

        await base.StartAsync(cancellationToken);
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        while (!stoppingToken.IsCancellationRequested)
        {
            var client = _serviceProvider.GetRequiredService<VehicleClient>()
                ?? throw new InvalidOperationException("Failed to get VehicleClient");
            
            _vehicles = await client.GetVehiclesAsync(3);

            _vehicleCacheService.SetCache(_vehicles);

            foreach (var vehicle in _vehicles)
            {
                Console.WriteLine("\tRetrieved vehicle: {0}, {1}", vehicle.Type, vehicle.Speed);
            }

            await Task.Delay(TimeSpan.FromSeconds(10), stoppingToken);
        }
    }
}
