using CarInfo.Model;
using CarInfo.Persistence;
using Microsoft.EntityFrameworkCore;

namespace CarInfo.Service;

public class CarService : ICarService
{
    private readonly CarDbContext _db;

    public CarService(CarDbContext db)
    {
        _db = db;
    }

    public async Task<Car?> GetCarAsync(int id)
    {
        return await _db.Cars.FindAsync(id);
    }

    public IEnumerable<Car> GetCars()
    {
        return _db.Cars.AsEnumerable();
    }

    public async Task CreateCarAsync(Car car)
    {
        _db.Cars.Add(car);
        await _db.SaveChangesAsync();
    }

    public async Task RemoveCarAsync(int id)
    {
        var foundCar = await _db.Cars.FindAsync(id);
        if (foundCar != null)
        {
            _db.Remove(foundCar);
            await _db.SaveChangesAsync();
        }
    }
}
