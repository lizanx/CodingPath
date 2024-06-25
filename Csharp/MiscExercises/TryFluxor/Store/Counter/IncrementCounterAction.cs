namespace TryFluxor.Store.Counter
{
    public class IncrementCounterAction
    {
        public int IncrementAmount { get; }

        public IncrementCounterAction(int incrementAmount)
        {
            IncrementAmount = incrementAmount;
        }
    }
}
