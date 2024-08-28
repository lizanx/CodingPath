// Tuple with named properties
var t1 = (Name: "Mary", Age: 18);
System.Console.WriteLine($"{t1}: Name = {t1.Name}, Age = {t1.Age}");
(string Name, int Age) t2 = ("Chloe", 23);
System.Console.WriteLine($"{t2}: Name = {t2.Name}, Age = {t2.Age}");

// Inferred tuple prop names
var obj = new { Name = "Christine", Age = 32 };
var t3 = (obj.Name, obj.Age);
System.Console.WriteLine($"{t3}: Name = {t3.Name}, Age = {t3.Age}");

// Desconstruct
Person p = new("Ken", 33);
var (name, age) = p;
System.Console.WriteLine($"Deconstruct: Name = {name}, Age = {age}");

class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void Deconstruct(out string Name, out int Age)
    {
        Name = this.Name;
        Age = this.Age;
    }
}
