using TryWaitAsync;

// Learn from Andrew's great blog post: https://andrewlock.net/just-because-you-stopped-waiting-for-it-doesnt-mean-the-task-stopped-running/

// Test 1: not finished task still running in background.
// var task1 = Hello.PrintHelloAsync();
// var completedTask = await Task.WhenAny(task1, Task.Delay(3000));
// if (completedTask == task1 && completedTask.IsCompleted)
// {
//     Console.WriteLine("Original task finished!");
// }
// else
// {
//     Console.WriteLine(
//         "Originial task not finished yet, wait for an input to see if it's still running."
//     );
//     Console.ReadKey();
// }

// Test 2: not finished task still running in background, using Task.WaitAsync()
// try
// {
//     await Hello.PrintHelloAsync().WaitAsync(TimeSpan.FromSeconds(5));
// }
// catch (Exception)
// {
//     Console.WriteLine("Timeout! Wait for an input to see if original task is still running.");
//     Console.ReadKey();
// }

// Test 3: truly cancel a task with CancellationToken
// using (var cts = new CancellationTokenSource())
// {
//     cts.CancelAfter(TimeSpan.FromSeconds(3));
//     try
//     {
//         await Hello.CancellablePrintHelloAsync(cts.Token).WaitAsync(TimeSpan.FromSeconds(5));
//     }
//     catch (OperationCanceledException)
//     {
//         Console.WriteLine("Original task successfully cancelled!");
//     }
//     catch
//     {
//         Console.WriteLine("Timeout!");
//     }
//     Console.WriteLine("Wait for an input to see if original task is still running.");
//     Console.ReadKey();
// }

// Test 4: use Task.WhenAny with Task.Delay(timeout, CancellationToekn) for safety
using (var helloCts = new CancellationTokenSource())
{
    helloCts.CancelAfter(TimeSpan.FromSeconds(3));
    var task = Hello.CancellablePrintHelloAsync(helloCts.Token);

    using var delayCts = new CancellationTokenSource();
    var completedTask = await Task.WhenAny(task, Task.Delay(5000, delayCts.Token));
    if (completedTask == task && completedTask.IsCompleted)
    {
        Console.WriteLine("Original task completed or cancelled, now cancel the delay task.");
        delayCts.Cancel();
    }
    else
    {
        Console.WriteLine("Timeout!");
    }
    Console.WriteLine("Wait for an input to see if original task is still running.");
    Console.ReadKey();
}
