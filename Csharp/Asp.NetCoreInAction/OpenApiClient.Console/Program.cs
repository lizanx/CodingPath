using Fruit;

var client = new FruitClient(
    "http://localhost:5191",
    new HttpClient()
);
Fruit.Fruit created = await client.FruitPOSTAsync(
    "123",
    new() { Name="Banana", Stock = 100 }
);
Console.WriteLine($"Fruit created: {created.Name}, {created.Stock}");
Fruit.Fruit fetched = await client.FruitGETAsync("123");
Console.WriteLine($"Fruit fetched: {fetched.Name}, {fetched.Stock}");
