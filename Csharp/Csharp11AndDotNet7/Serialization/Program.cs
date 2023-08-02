using System.Xml.Serialization;
using Packt.Shared;

using static System.Environment;
using static System.IO.Path;

List<Person> people = new()
{
    new(30000M)
    {
        FirstName = "Alice",
        LastName = "Smith",
        DateOfBirth = new(year: 1974, month: 3, day: 14)
    },
    new(40000M)
    {
        FirstName = "Bob",
        LastName = "Jones",
        DateOfBirth = new(year: 1969, month: 11, day: 23)
    },
    new(20000M)
    {
        FirstName = "Charlie",
        LastName = "Cox",
        DateOfBirth = new(year: 1984, month: 5, day: 4),
        Children = new()
        {
            new(0M)
            {
                FirstName = "Sally",
                LastName = "Cox",
                DateOfBirth = new(year: 2012, month: 7, day: 12)
            }
        }
    }
};

XmlSerializer xs = new(type: people.GetType());
string path = Combine(CurrentDirectory, "people.xml");
using (FileStream fs = File.Create(path))
{
    xs.Serialize(fs, people);
}

WriteLine($"Written {new FileInfo(path).Length} bytes of XML to {path}");
WriteLine();

// WriteLine(File.ReadAllText(path));


WriteLine("\nDeserialize from xml...");
using (FileStream xmlLoad = File.Open(path, FileMode.Open))
{
    List<Person>? loadedPeople = xs.Deserialize(xmlLoad) as List<Person>;
    if (loadedPeople is not null)
    {
        WriteLine("Loaded person list:");
        foreach (Person p in loadedPeople)
        {
            WriteLine(p);
        }
    }
    else
    {
        WriteLine("Failed to load person list.");
    }
}