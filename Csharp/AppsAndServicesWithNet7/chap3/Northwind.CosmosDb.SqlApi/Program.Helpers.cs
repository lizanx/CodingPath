partial class Program
{
    static void SectionTitle(string title)
    {
        ConsoleColor prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.DarkYellow;
        WriteLine("*");
        WriteLine($"* {title}");
        WriteLine("*");
        ForegroundColor = prevColor;
    }
}