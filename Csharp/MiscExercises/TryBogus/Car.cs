namespace TryBogus;

public class Car
{
    public string Brand { get; set; } = string.Empty;

    public string Model { get; set; } = string.Empty;

    public double Price { get; set; }

    public override string ToString()
    {
        return $"{Brand} Car, {Model}, ${Price}";
    }
}
