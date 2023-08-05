partial class Program
{
    static void SectionTitle(string title)
    {
        var prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.Yellow;
        WriteLine("*");
        WriteLine($"* {title}");
        WriteLine("*");
        ForegroundColor = prevColor;
    }

    static void Output(IEnumerable<string> cohort, string description = "")
    {
        if (!string.IsNullOrEmpty(description))
        {
            WriteLine(description);
        }
        WriteLine("---");
        WriteLine(string.Join(", ", cohort));
        WriteLine();
    }
}