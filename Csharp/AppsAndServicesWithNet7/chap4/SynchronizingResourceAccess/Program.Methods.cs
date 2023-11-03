partial class Program
{
    static void MethodA()
    {
        try
        {
            if (Monitor.TryEnter(SharedObjects.Conch, TimeSpan.FromSeconds(15)))
            // lock (SharedObjects.Conch)
            {
                for (int i = 0; i < 5; i++)
                {
                    Thread.Sleep(Random.Shared.Next(2000));
                    SharedObjects.Message += "A";
                    Interlocked.Increment(ref SharedObjects.Counter);
                    Write(".");
                }
            }
            else
            {
                WriteLine("MethodA timed out when entering a monitor on Conch.");
            }
        }
        finally
        {
            Monitor.Exit(SharedObjects.Conch);
        }
    }
    static void MethodB()
    {
        try
        {
            if (Monitor.TryEnter(SharedObjects.Conch, TimeSpan.FromSeconds(15)))
            // lock (SharedObjects.Conch)
            {
                for (int i = 0; i < 5; i++)
                {
                    Thread.Sleep(Random.Shared.Next(2000));
                    SharedObjects.Message += "B";
                    Interlocked.Increment(ref SharedObjects.Counter);
                    Write(".");
                }
            }
            else
            {
                WriteLine("MethodA timed out when entering a monitor on Conch.");
            }
        }
        finally
        {
            Monitor.Exit(SharedObjects.Conch);
        }
    }
}