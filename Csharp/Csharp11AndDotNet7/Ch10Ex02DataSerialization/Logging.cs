namespace Packt.Shared;

static class Logging
{
    private static void ColoredLog(string msg, ConsoleColor color)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = color;
        WriteLine(msg);
        ForegroundColor = prevColor;
    }

    public static void Info(string msg)
    {
        ColoredLog(msg, ConsoleColor.Blue);
    }
    public static void Warn(string msg)
    {
        ColoredLog(msg, ConsoleColor.Yellow);
    }
    public static void Error(string msg)
    {
        ColoredLog(msg, ConsoleColor.Red);
    }
}