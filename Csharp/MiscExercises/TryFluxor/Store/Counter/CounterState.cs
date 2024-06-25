using Fluxor;

namespace TryFluxor.Store.Counter
{
    [FeatureState]
    public class CounterState
    {
        private CounterState() { }

        public int Count { get; }

        public CounterState(int count)
        {
            Count = count;
        }
    }
}
