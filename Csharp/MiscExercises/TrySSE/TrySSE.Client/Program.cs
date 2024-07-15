using System.Net.ServerSentEvents;
using System.Text.Json;
using TrySSE.Shared;

using var client = new HttpClient();
using var stream = await client.GetStreamAsync("https://localhost:7249/sse");

await foreach (SseItem<object?> item in SseParser
    .Create(stream, (eventType, bytes) =>
        eventType switch
        {
            "Car" => JsonSerializer.Deserialize<Car>(bytes),
            "WeatherForecast" => JsonSerializer.Deserialize<WeatherForecast>(bytes) as object,
            _ => null
        })
    .EnumerateAsync())
{
    Console.WriteLine("Event Type: {0}", item.EventType);
    switch (item.Data)
    {
        case Car car:
            Console.WriteLine($"\tGot car: Brand({car.Brand}), Price({car.Price})");
            break;
        case WeatherForecast weatherForecast:
            Console.WriteLine($"\tGot weather forecast: Date({weatherForecast.Date}), Temperature({weatherForecast.TemperatureC}), Summary({weatherForecast.Summary})");
            break;
        default:
            Console.WriteLine("\tCouldn't deserialize the response.");
            break;
    }
}
