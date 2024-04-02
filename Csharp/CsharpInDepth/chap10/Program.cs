try
{
    ExceptionFilter.FilterExceptions();
}
catch (Exception e)
{
    Console.WriteLine($"Uncaught exception from filter, caught by Main: {e.Message}");
}

ExceptionFilter.DemoStackUnwind();
