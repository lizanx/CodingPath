using System.Collections.Concurrent;
using System.Diagnostics;

TryParallelForEach();
TryParallelInvoke();
await TryTaskWhenAll();
await TryTaskWhenAny();
await TryTaskRun();
await TryParallelForEachAsync();
return;


static void TryParallelForEach()
{
    var customers = new int[10];
    for (var i = 0; i < customers.Length; i++)
    {
        customers[i] = i;
    }

    Console.WriteLine("======== Sequential Execution ========");
    var sequentialTime = MeasureTime(() =>
    {
        foreach (var customer in customers)
        {
            ProcessPurchase(customer);
        }
    });
    Console.WriteLine($"========== Sequential Time Consumption: ${sequentialTime.TotalSeconds:F2}s ========");

    Console.WriteLine("======== Parallel Execution ========");
    var parallelTime = MeasureTime(() => { Parallel.ForEach(customers, ProcessPurchase); });
    Console.WriteLine($"========== Parallel Time Consumption: ${parallelTime.TotalSeconds:F2}s ========");
    return;

    TimeSpan MeasureTime(Action action)
    {
        var stopwatch = Stopwatch.StartNew();
        action();
        stopwatch.Stop();
        return stopwatch.Elapsed;
    }

    void ProcessPurchase(int customerId)
    {
        Console.WriteLine($"Customer-{customerId} purchase starts.");
        Thread.Sleep(TimeSpan.FromSeconds(1));
        Console.WriteLine($"Customer-{customerId} purchase ends.");
    }
}

static void TryParallelInvoke()
{
    Parallel.Invoke(() => PerformAction("A", 2),
        () => PerformAction("B", 3),
        () => PerformAction("C", 4));

    Console.WriteLine("All tasks finished.");
    return;

    void PerformAction(string name, int delay)
    {
        Console.WriteLine($"Starting {name} on thread {Thread.CurrentThread.ManagedThreadId}");
        Thread.Sleep(TimeSpan.FromSeconds(delay));
        Console.WriteLine($"Ending {name}");
    }
}

static async Task TryTaskWhenAll()
{
    var task1 = Task.Delay(1000).ContinueWith(_ => "Task 1 done");
    var task2 = Task.Delay(2000).ContinueWith(_ => "Task 2 done");
    var task3 = Task.Delay(3000).ContinueWith(_ => "Task 3 done");

    var allResults = await Task.WhenAll(task1, task2, task3);
    foreach (var result in allResults)
    {
        Console.WriteLine(result);
    }
    
    Console.WriteLine("All tasks finished.");
}

static async Task TryTaskWhenAny()
{
    var task1 = Task.Delay(3000).ContinueWith(_ => "Task 1 done");
    var task2 = Task.Delay(2000).ContinueWith(_ => "Task 2 done");
    var task3 = Task.Delay(1000).ContinueWith(_ => "Task 3 done");

    var firstFinished = await Task.WhenAny(task1, task2, task3);
    Console.WriteLine($"First finished: {await firstFinished}");
    
    Console.WriteLine("Other tasks may still be running...");
}

static async Task TryTaskRun()
{
    var result = await Task.Run(async () =>
    {
        await Task.Delay(2000);
        return "Task.Run finished";
    });
    Console.WriteLine("Result: {0}", result);
}

static async Task TryParallelForEachAsync()
{
    var userIds = Enumerable.Range(1, 100).ToList();
    var processedUsers = new ConcurrentBag<string>();
    var parallelOptions = new ParallelOptions { MaxDegreeOfParallelism = Environment.ProcessorCount };
    await Parallel.ForEachAsync(userIds, parallelOptions, async (userId, _) =>
    {
        var userData = await FetchUserData(userId);
        var processedResult = await ProcessUserData(userData);
        processedUsers.Add(processedResult);
    });
    Console.WriteLine($"Total processed users: {processedUsers.Count}");
    foreach (var data in processedUsers)
    {
        Console.WriteLine($"Processed user data: {data}");
    }
    return;

    async Task<string> FetchUserData(int userId)
    {
        await Task.Delay(100);
        return $"UserData-{userId}";
    }

    async Task<string> ProcessUserData(string userData)
    {
        await Task.Delay(50);
        return $"Processed-{userData}";
    }
}