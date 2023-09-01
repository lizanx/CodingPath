namespace HelperUtils;

public static class ColoredLog
{
    private static void Log(string msg, ConsoleColor color)
    {
        ConsoleColor prevColor = Console.ForegroundColor;
        Console.ForegroundColor = color;
        Console.WriteLine(msg);
        Console.ForegroundColor = prevColor;
    }

    public static void LogInfo(string msg)
    {
        Log(msg, ConsoleColor.Blue);
    }
    public static void LogWarn(string msg)
    {
        Log(msg, ConsoleColor.Yellow);
    }
    public static void LogError(string msg)
    {
        Log(msg, ConsoleColor.Red);
    }
}