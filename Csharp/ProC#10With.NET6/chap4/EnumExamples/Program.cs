ColorEnum green = ColorEnum.Green;
Console.WriteLine(
    "Type name: {0}, underlying type: {1}, value: {2}",
    green.GetType().Name,
    Enum.GetUnderlyingType(green.GetType()).Name,
    (int)green
);

Console.WriteLine("{0}All colors:", Environment.NewLine);
foreach (var color in Enum.GetValues<ColorEnum>())
{
    Console.WriteLine(color);
}
Console.WriteLine();

var edible = FoodEnum.Eatable | FoodEnum.Drinkable;
Console.WriteLine(
    "Edible is {0} and {1}",
    (edible | FoodEnum.Eatable) == edible ? "eatable" : "non-eatable",
    (edible | FoodEnum.Drinkable) == edible ? "drinkable" : "non-drinkable"
);

enum ColorEnum
{
    Red,
    Green,
    Blue
}

[Flags]
enum FoodEnum
{
    Eatable = 0b_1,
    Drinkable = 0b_10
}
