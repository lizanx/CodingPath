namespace TryWaitAsync;

public static class Hello
{
    public static async Task PrintHelloAsync()
    {
        for (int i = 0; i < 10; i++)
        {
            Console.WriteLine("Hello - {0}", i);
            await Task.Delay(1000);
        }
    }

    public static async Task CancellablePrintHelloAsync(CancellationToken cancellationToken)
    {
        for (int i = 0; i < 10; i++)
        {
            Console.WriteLine("Hello - {0}", i);
            cancellationToken.ThrowIfCancellationRequested();
            await Task.Delay(1000);
        }
    }
}
