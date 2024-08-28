var arr = new[] { "C#", "C++", "C", "Go", "Zig" };

System.Console.WriteLine("First 2:");
PrintArray(arr[0..2]);
PrintArray(arr[..2]);

System.Console.WriteLine("Last 3:");
PrintArray(arr[^3..^0]);
PrintArray(arr[^3..]);

Range middle = 1..^1;
System.Console.WriteLine("Middle(exclude first one and last one):");
PrintArray(arr[middle]);

Array.Reverse(arr);
System.Console.WriteLine("After reverse:");
PrintArray(arr);

Array.Clear(arr);
System.Console.WriteLine("After clear:");
PrintArray(arr);

static void PrintArray<T>(T[] arr)
{
    foreach (T item in arr)
    {
        Console.WriteLine(item + " ");
    }
    Console.WriteLine();
}
