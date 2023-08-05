using Microsoft.EntityFrameworkCore;
using System.Text.Json;
using Packt.Shared;

Category[]? categories = QueryCategoryWithProducts();
if (categories is null || !categories.Any())
{
    Logging.Error("No categories found, fail.");
    return;
}

using (Stream stream = File.Create(Path.Combine(Environment.CurrentDirectory, "data.json")))
{
    Logging.Info("Start serializing...");
    JsonSerializer.Serialize(
        stream,
        categories,
        typeof(Category[]),
        new JsonSerializerOptions() { WriteIndented = true }
    );
    Logging.Info("Serializing done.");
}
