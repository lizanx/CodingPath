using System.Reflection;
using MyNamespace;

var p1 = new Person("Natalia", 43);
var p2 = new Person("Sandra", 77);

Type t = typeof(Person);
var t1 = p1.GetType();
var t2 = p2.GetType();

Console.WriteLine($"Type name: {t.Name}");
Console.WriteLine($"Namespace: {t.Namespace}");
Console.WriteLine($"Is class: {t.IsClass}");
Console.WriteLine($"Is interface: {t.IsInterface}");
Console.WriteLine();

object? newInstance = Activator.CreateInstance(t, "Kelvin", 33);
if (newInstance is Person p)
{
    Console.WriteLine($"New person: {p.Name}");
    Console.WriteLine($"Need health care: {p.NeedHealthCare()}");
}
else
{
    Console.WriteLine("newInstance is not a valid Person!");
}
Console.WriteLine();

foreach (var method in t1.GetMethods())
{
    Console.WriteLine($"Method: {method.Name}");
    if (method.Name == "NeedHealthCare")
        Console.WriteLine("\tInvoking result: {0}", method.Invoke(p1, null));
}
Console.WriteLine();

var methodInfo = t1.GetMethod("NeedHealthCare");
if (methodInfo is not null)
{
    Console.WriteLine($"p2 needs health care: {methodInfo.Invoke(p2, null)}");
}
Console.WriteLine();

foreach (var property in t2.GetProperties())
{
    Console.WriteLine($"Property name: {property.Name}, value: {property.GetValue(p2)}");
}
Console.WriteLine();

var fieldInfo = t1.GetField("_age", BindingFlags.NonPublic | BindingFlags.Instance);
if (fieldInfo is not null)
{
    Console.WriteLine(
        $"Field name: {fieldInfo.Name}, in p1: {fieldInfo.GetValue(p1)}, in p2: {fieldInfo.GetValue(p2)}"
    );
}

namespace MyNamespace
{
    class Person
    {
        public string Name { get; set; }

        public Person(string name, int age)
        {
            Name = name;
            _age = age;
        }

        public bool NeedHealthCare() => _age >= 65;

        private int _age;
    }
}
