partial class Program
{
    static string AtoZ() => char.ConvertFromUtf32(Random.Shared.Next(65, 90));

    public static async IAsyncEnumerable<string> GetStockAsync()
    {
        for (int i = 0; i < 10; i++)
        {
            yield return $"{AtoZ()}{AtoZ()}{AtoZ()}{AtoZ()}";

            await Task.Delay(3000); // 3s
        }
    }
}