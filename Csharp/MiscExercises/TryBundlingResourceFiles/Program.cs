using System.Reflection;
using System.Resources;

Console.WriteLine("Demo Start");

// Console.WriteLine("App data: {0}", File.ReadAllText("app_data.txt"));

var assembly = Assembly.GetEntryAssembly()!;
using var appDataStream = assembly.GetManifestResourceStream(
    $"{assembly.GetName().Name}.app_data.txt"
)!;
using var reader = new StreamReader(appDataStream);
Console.WriteLine("App data: {0}", reader.ReadToEnd());

Console.WriteLine("Demo end");
