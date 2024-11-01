using System.Collections.ObjectModel;
using System.Collections.Specialized;

ObservableCollection<Person> people = new ObservableCollection<Person>
{
    new("Alice", 22),
    new("Bob", 17),
    new("Chris", 35)
};

people.CollectionChanged += PeopleChanged;
people.Add(new Person("Jane", 25));
people.RemoveAt(1);
people.Add(new Person("John", 55));
people.RemoveAt(0);
people.CollectionChanged -= PeopleChanged;

void PeopleChanged(object? sender, NotifyCollectionChangedEventArgs e)
{
    Console.WriteLine("People changed! Action: {0}", e.Action);

    if (e.Action == NotifyCollectionChangedAction.Add)
    {
        foreach (var person in e.NewItems!)
        {
            Console.WriteLine("\tAdded person: {0}", person);
        }
    }
    else if (e.Action == NotifyCollectionChangedAction.Remove)
    {
        foreach (var person in e.OldItems!)
        {
            Console.WriteLine("\tRemoved person: {0}", person);
        }
    }
}

class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public override string ToString()
    {
        return $"Person(Name: {Name}, Age: {Age})";
    }
}
