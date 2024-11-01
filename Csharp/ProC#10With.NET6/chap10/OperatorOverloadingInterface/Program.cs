using OperatorOverloadingInterface;

Point p1 = new();
Point p2 = new(1, 3);

Console.WriteLine($"Before any operations: p1 = {p1}, p2 = {p2}");

p1 = p1 + 3.0;
p2 = p2 + 3.0;
Console.WriteLine($"After + 3.0: p1 = {p1}, p2 = {p2}");

p1 = p1 - 2.0;
p2 = p2 - 2.0;
Console.WriteLine($"After - 2.0: p1 = {p1}, p2 = {p2}");

p1 = p1 * 5.0;
p2 = p2 * 5.0;
Console.WriteLine($"After * 5.0: p1 = {p1}, p2 = {p2}");

p1 = p1 / 2.0;
p2 = p2 / 2.0;
Console.WriteLine($"After / 2.0: p1 = {p1}, p2 = {p2}");
