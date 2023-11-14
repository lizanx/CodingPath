using System.Globalization;

partial class Program
{
    static void OutputCultures(string title)
    {
        ConsoleColor previousColor = ForegroundColor;
        ForegroundColor = ConsoleColor.DarkYellow;

        WriteLine("*");
        WriteLine($"* {title}");
        WriteLine("*");

        CultureInfo globalization = CultureInfo.CurrentCulture;
        CultureInfo localization = CultureInfo.CurrentUICulture;

        WriteLine("The current globalization culture is {0}: {1}",
            globalization.Name, globalization.DisplayName);
        
        WriteLine("The current localization culture is {0}: {1}",
            localization.Name, localization.DisplayName);
        
        WriteLine("Days of week: {0}",
            string.Join(", ", globalization.DateTimeFormat.DayNames));

        WriteLine("Months of the year: {0}",
            string.Join(", ", globalization.DateTimeFormat
                .MonthNames.TakeWhile(month => !string.IsNullOrEmpty(month))));
        
        WriteLine("1st day of this year: {0}",
            new DateTime(year: DateTime.Today.Year, month: 1, day: 1).ToString("D", globalization));
        
        WriteLine("Number group separator: {0}", globalization.NumberFormat.NumberGroupSeparator);

        WriteLine("Number decimal separator: {0}", globalization.NumberFormat.NumberDecimalSeparator);

        RegionInfo region = new(globalization.LCID);

        WriteLine("Currency symbol: {0}", region.CurrencySymbol);

        WriteLine("Currency name: {0} ({1})", region.CurrencyNativeName, region.CurrencyEnglishName);

        WriteLine("IsMetric: {0}", region.IsMetric);

        WriteLine();

        ForegroundColor = previousColor;
    }
}