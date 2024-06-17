using CarInfo.Model;
using CarInfo.Service;

namespace CarInfo.Test;

public class StubCarService : ICarService
{
    private readonly List<Car> _cars = [
        new ("Posche", "Taycan") { Id = 1 },
        new ("NIO", "ET5") { Id = 2 },
        new ("Zeekr", "001") { Id = 3 },
        new ("BMW", "i5")  { Id = 4 }
    ];

    public Task<Car?> GetCarAsync(int id)
    {
        return Task.FromResult(_cars.Find(c => c.Id == id));
    }

    public IEnumerable<Car> GetCars()
    {
        return _cars;
    }

    public Task CreateCarAsync(Car car)
    {
        if (!_cars.Any(c => c.Id == car.Id))
        {
            _cars.Add(car);
        }
        return Task.CompletedTask;
    }

    public Task RemoveCarAsync(int id)
    {
        if (_cars.Find(c => c.Id == id) is Car found)
        {
            _cars.Remove(found);
        }

        return Task.CompletedTask;
    }
}
