using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text.Json;

namespace GetStartedApp.Services;

public class LocalDataAccessService<T> : IDataAccessService<T>
{
    public IEnumerable<T>? GetAll()
    {
        var fileName = typeof(T).Name;
        var filePath = Path.Combine(Environment.CurrentDirectory, "Assets", "Data", fileName + ".json");
        Debug.WriteLine($"### Try to read from file: {filePath} ###");
        return !File.Exists(filePath) ? null : JsonSerializer.Deserialize<IEnumerable<T>>(File.ReadAllText(filePath));
    }
}