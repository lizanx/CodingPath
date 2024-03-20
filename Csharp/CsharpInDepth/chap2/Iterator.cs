static class Iterator
{
    public static IEnumerable<string> GetString()
    {
        try
        {
            Console.WriteLine("Before 1st string");
            yield return "1st string";
            Console.WriteLine("Between 1st and 2nd strings");
            yield return "2nd string";
            Console.WriteLine("Between 2nd and 3rd strings");
            yield return "3rd string";
        }
        finally
        {
            Console.WriteLine("Finally block called!");
        }
    }
}