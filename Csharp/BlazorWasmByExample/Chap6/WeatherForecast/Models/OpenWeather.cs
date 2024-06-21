namespace WeatherForecast.Models;

public class OpenWeather
{
    public Daily[] Daily { get; set; } = default!;
}
public class Daily
{
    public long Dt { get; set; }
    public Temp Temp { get; set; } = default!;
    public Weather[] Weather { get; set; } = default!;
}
public class Temp
{
    public double Min { get; set; }
    public double Max { get; set; }
}
public class Weather
{
    public string Description { get; set; } = default!;
    public string Icon { get; set; } = default!;
}
