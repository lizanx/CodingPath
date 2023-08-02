partial class Program {
    static void SectionTitle(string title)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.Yellow;
        WriteLine("*");
        WriteLine($"* {title}");
        WriteLine("*");
        ForegroundColor = prevColor;
    }

    static void Info(string msg)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.Blue;
        WriteLine(msg);
        ForegroundColor = prevColor;
    }
    static void Warn(string msg)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.DarkYellow;
        WriteLine(msg);
        ForegroundColor = prevColor;
    }
    static void Error(string msg)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.Red;
        WriteLine(msg);
        ForegroundColor = prevColor;
    }
}