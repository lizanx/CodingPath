foreach (int i in Fibonacci.GenerateSequence())
{
    Console.WriteLine($"Fibonacci num: {i}");
    if (i > 20)
    {
        break;
    }
}

foreach (int i in SequenceGenerator.Generate((current: 0, next: 1), pair => (pair.next, pair.current + pair.next), pair => pair.current))
{
    Console.WriteLine($"Fibonacci Generator: {i}");
    if (i > 20)
    {
        break;
    }
}

DynamicTuple.DemoCompileTimeBind();
DynamicTuple.DemoExecutionTimeBind();
