using System.Threading.Channels;

var channel = Channel.CreateUnbounded<string>();

_ = Task.Run(async () =>
{
    for (var i = 0; i < 10; ++i)
    {
        await channel.Writer.WriteAsync($"Message[{i}]");
        Console.WriteLine("Produced: {0}", i);
        await Task.Delay(200);
    }

    channel.Writer.Complete();
});

await foreach (var msg in channel.Reader.ReadAllAsync())
{
    Console.WriteLine("Received: {0}", msg);
    await Task.Delay(250);
}

Console.WriteLine("Processing complete.");
