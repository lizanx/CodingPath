using System.Text;

namespace TryBogus;

public class CarOwner
{
    public string Name { get; set; } = string.Empty;

    public string Address { get; set; } = string.Empty;

    public int Age { get; set; }

    public IList<Car> Cars = [];

    public override string ToString()
    {
        var sb = new StringBuilder();

        sb.Append($"{Name}:\n");
        sb.Append($"\t- Address: {Address}\n");
        sb.Append($"\t- Age: {Age}\n");
        sb.Append("\t- Cars:\n");

        foreach (var car in Cars)
        {
            sb.Append($"\t\t* {car}\n");
        }

        return sb.ToString();
    }
}
