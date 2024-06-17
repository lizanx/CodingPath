using CarInfo.Persistence;
using CarInfo.Service;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;

namespace CarInfo.Test;

public class CarInfoMockDbTest
{
    [Fact]
    public async Task CarInfo_GetZeekrCar()
    {
        var connection = new SqliteConnection("DataSource=:memory:");
        connection.Open();

        var options = new DbContextOptionsBuilder<CarDbContext>().UseSqlite(connection).Options;

        using (var context = new CarDbContext(options))
        {
            context.Database.EnsureCreated();
            context.Cars.AddRange(
                [
                    new("Posche", "Taycan") { Id = 1 },
                    new("NIO", "ET5") { Id = 2 },
                    new("Zeekr", "001") { Id = 3 },
                    new("BMW", "i5") { Id = 4 }
                ]
            );
            context.SaveChanges();
        }

        using (var context = new CarDbContext(options))
        {
            var carService = new CarService(context);
            var car = await carService.GetCarAsync(3);
            Assert.NotNull(car);
            Assert.Equal(3, car.Id);
            Assert.Equal("Zeekr", car.Brand);
            Assert.Equal("001", car.Model);
        }
    }
}
