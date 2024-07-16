using Bogus;
using TryBogus;

Randomizer.Seed = new Random(DateTime.UtcNow.Millisecond);

var fakeCars = new Faker<Car>()
    .StrictMode(true)
    .RuleFor(car => car.Brand, f => f.Vehicle.Manufacturer())
    .RuleFor(car => car.Model, f => f.Vehicle.Model())
    .RuleFor(car => car.Price, f => (double)f.Finance.Amount());

var fakeCarOwners = new Faker<CarOwner>()
    .StrictMode(true)
    .RuleFor(owner => owner.Name, f => f.Person.FullName)
    .RuleFor(owner => owner.Age, f => DateTime.Now.Year - f.Person.DateOfBirth.Year)
    .RuleFor(owner => owner.Address, f => f.Address.FullAddress())
    .RuleFor(owner => owner.Cars, f => fakeCars.Generate(Random.Shared.Next(1, 5)));

foreach (var carOwner in fakeCarOwners.GenerateBetween(3, 10))
{
    Console.WriteLine(carOwner);
}
