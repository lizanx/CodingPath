using System.Text;

static class TupleDeconstructionOrder
{
    public static void DemoTupleDeconstructionOrder()
    {
        StringBuilder builder = new ("12345", 5);
        StringBuilder originalBuilder = builder;

        (builder, builder.Length) = (new StringBuilder("67890"), 3);

        Console.WriteLine($"Original(len={originalBuilder.Length}): {originalBuilder}");
        Console.WriteLine($"After deconstruction(len={builder.Length}): {builder}");
    }
}