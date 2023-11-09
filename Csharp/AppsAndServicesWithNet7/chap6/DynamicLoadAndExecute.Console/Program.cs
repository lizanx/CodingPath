Assembly? thisAssembly = Assembly.GetEntryAssembly();

if (thisAssembly is null)
{
    WriteLine("Couldn't get the entry assembly.");
    return;
}

OutputAssemblyInfo(thisAssembly);

WriteLine("Creating load context for :\n {0}\n",
    Path.GetFileName(thisAssembly.Location));

DemoAssemblyLoadContext loadContext = new(thisAssembly.Location);

string assemblyPath = Path.Combine(
    Path.GetDirectoryName(thisAssembly.Location) ?? "",
    "DynamicLoadAndExecute.Library.dll"
);

WriteLine("Loading:\n {0}\n", Path.GetFileName(assemblyPath));

Assembly dogAssembly = loadContext.LoadFromAssemblyPath(assemblyPath);

OutputAssemblyInfo(dogAssembly);

Type? dogType = dogAssembly.GetType("DynamicLoadAndExecute.Library.Dog");

if (dogType is null)
{
    WriteLine("Couldn't get the Dog type.");
    return;
}

MethodInfo? info = dogType.GetMethod("Speak");

if (info is not null)
{
    object? dog = Activator.CreateInstance(dogType);

    for (int i = 0; i < 10; i++)
    {
        info.Invoke(dog, new[] { "Fido" });
    }
}

WriteLine();
WriteLine("Unloading context and assemblies.");
loadContext.Unload();
