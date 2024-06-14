using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using SharedLib;

namespace ApiClient.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;

    public IEnumerable<WeatherForecast>? WeatherForecasts { get; set; }

    public IEnumerable<Vehicle>? Vehicles { get; set; }

    public IndexModel(ILogger<IndexModel> logger)
    {
        _logger = logger;
    }

    public async Task<IActionResult> OnGet([FromServices] IHttpClientFactory factory,
        // [FromServices] VehicleClient vehicleClient)
        [FromServices] VehicleCacheService vehicleCacheService)
    {
        HttpClient weatherClient = factory.CreateClient("weatherforecast")
            ?? throw new InvalidOperationException("Cannot get weatherforecast client");
        
        WeatherForecasts = await weatherClient.GetFromJsonAsync<IEnumerable<WeatherForecast>>("");

        // Vehicles = await vehicleClient.GetVehiclesAsync(4);
        Vehicles = vehicleCacheService.Vehicles;

        return Page();
    }
}
