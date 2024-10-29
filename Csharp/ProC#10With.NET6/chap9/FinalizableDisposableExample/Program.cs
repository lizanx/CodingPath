{
    // Test case: using Finalizer
    Console.WriteLine("### Test Case 1 - Use Finalizer ###");
    TestClass? testObj = new();
    testObj = null;
    GC.Collect();
    GC.WaitForPendingFinalizers();
}


{
    // Test case: using IDisposable
    Console.WriteLine(Environment.NewLine);
    Console.WriteLine("### Test Case 2 - Use IDisposable ###");
    using TestClass testObj = new();
    testObj.Dispose(); // Duplicated call to Dispose is ok
    testObj.Dispose(); // Duplicated call to Dispose is ok
}

class TestClass : IDisposable
{
    private bool _disposed;

    public TestClass()
    {
        Console.WriteLine("TestClass object constructed.");
    }

    ~TestClass()
    {
        Cleanup(false);
        Console.WriteLine("TestClass object finalized.");
    }

    public void Dispose()
    {
        Cleanup(true);
        GC.SuppressFinalize(this);
        Console.WriteLine("TestClass object disposed.");
    }

    private void Cleanup(bool disposing)
    {
        if (!_disposed)
        {
            if (disposing)
            {
                Console.WriteLine("\tDisposing managed resources which are disposable...");
            }
            Console.WriteLine("\tCleaning up unmanaged resources...");
            _disposed = true;
        }
    }
}
