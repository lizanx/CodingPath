using Packt.Shared;

static class ColoredLog
{
    internal static void Log(string msg, ConsoleColor color)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = color;
        WriteLine(msg);
        ForegroundColor = prevColor;
    }

    public static void Title(string msg)
    {
        Log(msg, ConsoleColor.Yellow);
    }
    public static void Warn(string msg)
    {
        Log(msg, ConsoleColor.DarkYellow);
    }
}

partial class Program
{
    static void SectionTitle(string title)
    {
        ColoredLog.Title("*" + Environment.NewLine + $"* {title}" +
            Environment.NewLine + "*" + Environment.NewLine);
    }

    static void Fail(string msg)
    {
        ColoredLog.Log($"Fail > {msg}", ConsoleColor.Red);
    }
    static void Info(string msg)
    {
        ColoredLog.Log($"Info > {msg}", ConsoleColor.Cyan);
    }
}