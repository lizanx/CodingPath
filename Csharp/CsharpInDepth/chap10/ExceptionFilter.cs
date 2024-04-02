static class ExceptionFilter
{
    public static string[] messages =
    [
        "You can catch this.",
        "You can catch this too.",
        "This won't be caught."
    ];

    public static void FilterExceptions()
    {
        foreach (string msg in messages)
        {
            try
            {
                throw new Exception(msg);
            }
            catch (Exception e)
                when (e.Message.Contains("catch"))
            {
                Console.WriteLine($"Exeption caught by filter: {e.Message}");
            }
        }
    }

    public static void DemoStackUnwind()
    {
        Bottom();
    }

    private static bool LogAndReturn(string message, bool ret)
    {
        Console.WriteLine(message);
        return ret;
    }

    private static void Top()
    {
        try
        {
            throw new Exception("Exception thrown from Top");
        }
        finally
        {
            Console.WriteLine("Top finally.");
        }
    }

    private static void Middle()
    {
        try
        {
            Top();
        }
        catch (Exception e)
            when (LogAndReturn("Middle filter", false))
        {
            Console.WriteLine("Caught in middle: {0}", e.Message);
        }
        finally
        {
            Console.WriteLine("Middle finally.");
        }
    }

    private static void Bottom()
    {
        try
        {
            Middle();
        }
        catch (IOException e)
            when (LogAndReturn("Never called", true))
        {
            Console.WriteLine("IOException caught in Bottom: {0}", e.Message);
        }
        catch (Exception e)
            when (LogAndReturn("Bottom filter", true))
        {
            Console.WriteLine("Caught in Bottom: {0}", e.Message);
        }
    }
}