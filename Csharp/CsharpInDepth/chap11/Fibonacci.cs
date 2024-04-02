static class Fibonacci
{
    public static IEnumerable<int> GenerateSequence()
    {
        var pair = (current: 0, next: 1);
        while (true)
        {
            yield return pair.current;
            pair = (pair.next, pair.current + pair.next);
        }
    }
}