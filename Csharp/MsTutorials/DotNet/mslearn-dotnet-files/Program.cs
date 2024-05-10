using System.Text.Json;

var salesTotalDir = Path.Combine(Directory.GetCurrentDirectory(), "salesTotalDir");
Directory.CreateDirectory(salesTotalDir);

var salesFiles = FindJsonFiles(Path.Combine(Directory.GetCurrentDirectory(), "stores"));
File.AppendAllText(Path.Combine(salesTotalDir, "totals.txt"), $"{CalculateSalesTotal(salesFiles)}{Environment.NewLine}");

// File.WriteAllText(Path.Combine(salesTotalDir, "totals.txt"), string.Empty);

static IEnumerable<string> FindJsonFiles(string folderName) =>
    Directory.EnumerateFiles(folderName, "*.json", SearchOption.AllDirectories);

double CalculateSalesTotal(IEnumerable<string> salesFiles)
{
    double salesTotal = 0;

    foreach (var salesFile in salesFiles)
    {
        var salesData = JsonSerializer.Deserialize<SalesData>(File.ReadAllText(salesFile));
        salesTotal += salesData?.Total ?? 0;
    }

    return salesTotal;
}

record SalesData (double Total);
