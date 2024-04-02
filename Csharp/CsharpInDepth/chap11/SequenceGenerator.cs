static class SequenceGenerator
{
    public static IEnumerable<TResult> Generate<TState, TResult>(
        TState seed,
        Func<TState, TState> generator,
        Func<TState, TResult> resultSelector
    )
    {
        TState state = seed;
        while (true)
        {
            yield return resultSelector(state);
            state = generator(state);
        }
    }
}