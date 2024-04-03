static class DynamicTuple
{
    public static void DemoCompileTimeBind()
    {
        var t = (1, 2, 3, 4, 5, 6, 7, 8, 9);
        Console.WriteLine(t.Item9);
    }

    public static void DemoExecutionTimeBind()
    {
        dynamic t = (1, 2, 3, 4, 5, 6, 7, 8, 9);
        try
        {
            Console.WriteLine(t.Item9);
        }
        catch (Exception e)
        {
            Console.WriteLine("Failed to access Item9 in execution: {0}", e);
        }
    }
}