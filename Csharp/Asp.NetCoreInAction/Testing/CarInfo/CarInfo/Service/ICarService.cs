using CarInfo.Model;

namespace CarInfo.Service;

public interface ICarService
{
    Task<Car?> GetCarAsync(int id);
    IEnumerable<Car> GetCars();
    Task CreateCarAsync(Car car);
    Task RemoveCarAsync(int id);
}
