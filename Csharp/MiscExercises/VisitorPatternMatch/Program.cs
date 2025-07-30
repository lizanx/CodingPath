using System.Diagnostics;

var isVisitorPattern = true;

while (true)
{
    Console.Write("Please enter your input: ");
    var input = Console.ReadLine();
    if (input is not null && input.ToLower() == "q")
        break;

    if (isVisitorPattern)
    {
        var value = ParseVisitor(input);
        Console.WriteLine("\t> Your input {0} valid.", value.Accept(VisitorPattern.ValueValidationVisitor.Instance) ? "is" : "is not");
    }
    else
    {
        var value = ParseNormal(input);
        Console.WriteLine("\t> Your input {0} valid.", Normal.ValidationHelper.IsValid(value) ? "is" : "is not");
    }
}

static Normal.IValue ParseNormal(string? input)
{
    if (long.TryParse(input, out var number))
    {
        return new Normal.NumericValue(number);
    }
    if (DateTimeOffset.TryParse(input, out var dateTimeOffset))
    {
        return new Normal.DateTimeValue(dateTimeOffset);
    }
    return new Normal.StringValue(input);
}

static VisitorPattern.IValue ParseVisitor(string? input)
{
    if (long.TryParse(input, out var number))
    {
        return new VisitorPattern.NumericValue(number);
    }
    if (DateTimeOffset.TryParse(input, out var dateTimeOffset))
    {
        return new VisitorPattern.DateTimeValue(dateTimeOffset);
    }
    return new VisitorPattern.StringValue(input);
}

namespace Normal
{
    // Normal case without visitor pattern.
    public interface IValue { }

    public record StringValue(string? Value) : IValue;

    public record NumericValue(long Value) : IValue;

    public record DateTimeValue(DateTimeOffset Value) : IValue;

    public static class ValidationHelper
    {
        public static bool IsValid(IValue value) =>
            value switch
            {
                StringValue strValue => !string.IsNullOrWhiteSpace(strValue.Value),
                NumericValue numValue => numValue.Value >= 0,
                // DateTimeValue dateValue => dateValue.Value <= DateTimeOffset.Now,
                _ => throw new UnreachableException("Failed to recognize type of value.")
            };
    }

}

namespace VisitorPattern
{
    public interface IValue
    {
        T Accept<T>(IValueVisitor<T> visitor);
    }

    public record StringValue(string? Value) : IValue
    {
        public T Accept<T>(IValueVisitor<T> visitor) => visitor.Visit(this);
    }

    public record NumericValue(long Value) : IValue
    {
        public T Accept<T>(IValueVisitor<T> visitor) => visitor.Visit(this);
    }

    public record DateTimeValue(DateTimeOffset Value) : IValue
    {
        public T Accept<T>(IValueVisitor<T> visitor) => visitor.Visit(this);
    }

    public interface IValueVisitor<out T>
    {
        T Visit(StringValue value);
        T Visit(NumericValue value);
        T Visit(DateTimeValue value);
    }

    public class ValueValidationVisitor : IValueVisitor<bool>
    {
        public bool Visit(StringValue value) => !string.IsNullOrWhiteSpace(value.Value);

        public bool Visit(NumericValue value) => value.Value >= 0;

        public bool Visit(DateTimeValue value) => value.Value <= DateTimeOffset.Now;

        public static ValueValidationVisitor Instance => _instance;

        private static readonly ValueValidationVisitor _instance;

        private ValueValidationVisitor() { }

        static ValueValidationVisitor()
        {
            _instance = new();
        }
    }

}
