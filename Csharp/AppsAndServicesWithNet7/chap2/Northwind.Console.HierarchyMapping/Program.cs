using Microsoft.EntityFrameworkCore;
using Northwind.Console.HierarchyMapping;

DbContextOptionsBuilder<HierarchyDb> options = new();
options.UseSqlServer("Data Source=.;Initial Catalog=HierarchyMapping;Integrated Security=true;TrustServerCertificate=true;");

using (HierarchyDb db = new(options.Options))
{
    bool deleted = await db.Database.EnsureDeletedAsync();
    WriteLine($"Database deleted: {deleted}");

    bool created = await db.Database.EnsureCreatedAsync();
    WriteLine($"Database created: {created}");

    WriteLine("SQL script used to create the database:");
    WriteLine(db.Database.GenerateCreateScript());

    if (db.Students is null || !db.Students.Any())
    {
        WriteLine("There're no students.");
    }
    else
    {
        foreach (Student student in db.Students)
        {
            WriteLine($"{student.Name} studies {student.Subject}");
        }
    }
    if (db.Employees is null || !db.Employees.Any())
    {
        WriteLine("There're no employees.");
    }
    else
    {
        foreach (Employee employee in db.Employees)
        {
            WriteLine($"{employee.Name} was hired on {employee.HireDate}");
        }
    }
    if (db.People is null || !db.People.Any())
    {
        WriteLine("There're no people.");
    }
    else
    {
        foreach (Person person in db.People)
        {
            WriteLine($"{person.Name} has ID of {person.Id}");
        }
    }
    
}