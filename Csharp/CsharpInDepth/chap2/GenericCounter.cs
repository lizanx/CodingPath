class GenericCounter<T>
{
    private static int value;

    static GenericCounter()
    {
        Console.WriteLine($"Initializing counter for type {typeof(T)}");
    }

    public static void Increment()
    {
        value++;
    }

    public static void Display()
    {
        Console.WriteLine($"Counter for type {typeof(T)} is {value}");
    }
}