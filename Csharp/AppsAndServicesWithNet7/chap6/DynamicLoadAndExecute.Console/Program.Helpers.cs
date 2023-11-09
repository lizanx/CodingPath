partial class Program
{
    static void OutputAssemblyInfo(Assembly a)
    {
        WriteLine($"FullName: {a.FullName}");
        WriteLine($"Location: {Path.GetDirectoryName(a.Location)}");
        WriteLine($"IsCollectible: {a.IsCollectible}");
        WriteLine("Defined types:");
        foreach (TypeInfo info in a.DefinedTypes)
        {
            if (!info.Name.EndsWith("Attribute"))
            {
                WriteLine($"  Name: {info.Name}, Members: {info.GetMembers().Length}");
            }
        }
        WriteLine();
    }
}