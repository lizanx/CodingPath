using System.Diagnostics;

Write("Press ENTER to start:");
ReadLine();

Stopwatch watch = Stopwatch.StartNew();

watch.Start();

int max = 45;
IEnumerable<int> numbers = Enumerable.Range(start: 1, count: max);
WriteLine($"Calculating Fibonacci sequence up to term {max}. Please wait...");
int[] fobonaccis = numbers
    .AsParallel() // Run in parallel
    .Select( n => Fibonacci(n) )
    .OrderBy( n => n ) // Order after parallel computing
    .ToArray();

watch.Stop();

WriteLine($"{watch.ElapsedMilliseconds:#, ##0} elapsed milliseconds.");

WriteLine("Results:");
foreach (int n in fobonaccis)
{
    Write($"{n:N0} ");
}

static int Fibonacci(int term) =>
    term switch
    {
        1 => 0,
        2 => 1,
        _ => Fibonacci(term - 2) + Fibonacci(term - 1)
    };