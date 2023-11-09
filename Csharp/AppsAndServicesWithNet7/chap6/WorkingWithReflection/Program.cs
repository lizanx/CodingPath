using System.Reflection;
using Packt.Shared;

WriteLine("Assembly metadata:");
Assembly? assembly = Assembly.GetEntryAssembly();

if (assembly is null)
{
    WriteLine("Failed to get entry assembly.");
    return;
}

WriteLine($"\tFull Name: {assembly.FullName}");
WriteLine($"\tLocation: {assembly.Location}");
WriteLine($"\tEntry Point: {assembly.EntryPoint}");

IEnumerable<Attribute> attributes = assembly.GetCustomAttributes();
WriteLine("\tAssembly-Level Attributes:");
foreach (Attribute attribute in attributes)
{
    WriteLine($"\t\t{attribute.GetType()}");
}

AssemblyInformationalVersionAttribute? version =
    assembly.GetCustomAttribute<AssemblyInformationalVersionAttribute>();
WriteLine($"** Version: {version?.InformationalVersion}");

AssemblyCompanyAttribute? company =
    assembly.GetCustomAttribute<AssemblyCompanyAttribute>();
WriteLine($"** Company: {company?.Company}");

WriteLine();
WriteLine("** Types:");
Type[] types = assembly.GetTypes();

foreach (Type type in types)
{
    WriteLine();
    WriteLine($"Type: {type.Name}");
    MemberInfo[] members = type.GetMembers();

    foreach (MemberInfo member in members)
    {
        ObsoleteAttribute? obsolete = member.GetCustomAttribute<ObsoleteAttribute>();

        WriteLine("\t{0}: {1} ({2}) {3}",
            member.MemberType, member.Name, member.DeclaringType?.Name,
            obsolete is null ? "" : $"Obsolete! {obsolete.Message}");
        
        IOrderedEnumerable<CoderAttribute> coders =
            member.GetCustomAttributes<CoderAttribute>()
            .OrderByDescending(c => c.LastModified);
        
        foreach (CoderAttribute coder in coders)
        {
            WriteLine("\t-> Modified by {0} on {1}", coder.Coder, coder.LastModified);
        }
    }
}