using Microsoft.EntityFrameworkCore;

namespace CarInfo.Model;

public class Car
{
    public int Id { get; set; }

    public string Brand { get; set; }

    public string Model { get; set; }
    
    public Car(string brand, string model)
    {
        Brand = brand;
        Model = model;
    }
}
