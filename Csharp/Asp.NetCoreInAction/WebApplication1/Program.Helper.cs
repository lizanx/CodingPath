partial class Program
{
    private static void ColoredLog(string msg, ConsoleColor color)
    {
        ConsoleColor prevColor = Console.ForegroundColor;
        Console.ForegroundColor = color;
        Console.WriteLine(msg);
        Console.ForegroundColor = prevColor;
    }

    public static void LogInfo(string msg)
    {
        ColoredLog(msg, ConsoleColor.Blue);
    }
    public static void LogWarn(string msg)
    {
        ColoredLog(msg, ConsoleColor.Yellow);
    }
    public static void LogError(string msg)
    {
        ColoredLog(msg, ConsoleColor.Red);
    }
}