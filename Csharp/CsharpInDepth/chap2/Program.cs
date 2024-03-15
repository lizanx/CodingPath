// See https://aka.ms/new-console-template for more information
using StringGenericCounter = GenericCounter<string>;
using IntGenericCounter = GenericCounter<int>;

Console.WriteLine("\nGeneric counter:");
StringGenericCounter.Display();
StringGenericCounter.Increment();
StringGenericCounter.Increment();
StringGenericCounter.Display();
IntGenericCounter.Display();
IntGenericCounter.Increment();
IntGenericCounter.Increment();
IntGenericCounter.Increment();
IntGenericCounter.Display();


Console.WriteLine("\nDefault values:");
Console.WriteLine("Default value of int: {0}", default(int));
Console.WriteLine("Default value of bool: {0}", default(bool));
Console.WriteLine("Default value of string: {0}", default(string));
Console.WriteLine("Default value of class: {0}", default(DefaultClass));
Console.WriteLine("Default value of class, is null? {0}", default(DefaultClass) == null);
Console.WriteLine("Default value of struct: {0}", default(DefaultStruct));
