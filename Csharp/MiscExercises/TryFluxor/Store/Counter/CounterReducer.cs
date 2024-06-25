using Fluxor;

namespace TryFluxor.Store.Counter
{
    public static class CounterReducer
    {
        [ReducerMethod]
        public static CounterState ReduceIncrementCounterAction(CounterState state, IncrementCounterAction action) =>
            new CounterState(state.Count + action.IncrementAmount);
    }
}
