// Integer and floating points
using System.Numerics;

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
System.Console.WriteLine("'0' is digit? {0}, {1}", char.IsDigit(str[0]), char.IsDigit(str, 0));
System.Console.WriteLine("'h' is letter? {0}, {1}", char.IsLetter('h'), char.IsLetter("hello", 0));
System.Console.WriteLine(
    "'?' is punctuation? {0}, {1}",
    char.IsPunctuation('?'),
    char.IsPunctuation("Who's that?", 3)
);
System.Console.WriteLine(
    "' ' is whitespace? {0}, {1}",
    char.IsWhiteSpace(' '),
    char.IsWhiteSpace("I am xx", 1)
);

// Parse and TryParse
try
{
    var d = double.Parse("1.22");
    System.Console.WriteLine("Successfully parsed doubel: {0}", d);
}
catch
{
    System.Console.WriteLine("Failed to parse double!");
}
if (double.TryParse("1.22", out double d2))
{
    System.Console.WriteLine("Successfully try-parsed doubel: {0}", d2);
}
else
{
    System.Console.WriteLine("Failed to try-parse double!");
}

// Big integers
var biggy = BigInteger.Parse("999999999999999999999999999999999");
System.Console.WriteLine(
    "Biggy: {0}{1}Is event: {2}, is power of 2: {3}",
    biggy,
    Environment.NewLine,
    biggy.IsEven,
    biggy.IsPowerOfTwo
);
var bigger = biggy * BigInteger.Parse("8888888888888888888888888888888888");
System.Console.WriteLine(
    "Bigger: {0}{1}Is event: {2}, is power of 2: {3}",
    bigger,
    Environment.NewLine,
    bigger.IsEven,
    bigger.IsPowerOfTwo
);

// Separators
System.Console.WriteLine("Binary: {0}", 0b_01_01);
System.Console.WriteLine("Hex: {0}", 0x_ab_cd);
