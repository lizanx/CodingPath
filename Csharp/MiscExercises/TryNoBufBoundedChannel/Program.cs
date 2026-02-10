using System.Threading.Channels;

var channel = Channel.CreateBounded<int>(0);

var producer = Task.Run(async () =>
{
    for (int i = 0; i < 10; ++i)
    {
        Console.WriteLine($"[Producer] Producing data {i} - {DateTimeOffset.Now}");
        await channel.Writer.WriteAsync(i);
        Console.WriteLine($"[Producer] Produced data {i} - {DateTimeOffset.Now}");
    }
    channel.Writer.Complete();
});

var consumer = Task.Run(async () =>
{
    await foreach (int i in channel.Reader.ReadAllAsync())
    {
        Console.WriteLine($"[Consumer] Consuming data {i} - {DateTimeOffset.Now}");
        await Task.Delay(500);
        Console.WriteLine($"[Consumer] Consumed data {i} - {DateTimeOffset.Now}");
    }
});

await Task.WhenAll(producer, consumer);

Console.WriteLine("=== All Done ===");
