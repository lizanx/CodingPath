// Integer and floating points
System.Console.WriteLine("int max: {0}", int.MaxValue);
System.Console.WriteLine("int min: {0}", int.MinValue);
System.Console.WriteLine("double max: {0}", double.MaxValue);
System.Console.WriteLine("double min: {0}", double.MinValue);
System.Console.WriteLine("double epsilon: {0}", double.Epsilon);
System.Console.WriteLine("double positive infinity: {0}", double.PositiveInfinity);
System.Console.WriteLine("double negative infinity: {0}", double.NegativeInfinity);

// Boolean
System.Console.WriteLine("bool false string: {0}", bool.FalseString);
System.Console.WriteLine("bool true string: {0}", bool.TrueString);

// Char
string str = "3:Hello, C#!";
System.Console.WriteLine("{0}, {1}", char.IsDigit(str[0]), char.IsDigit(str, 0));
