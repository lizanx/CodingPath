using System.Diagnostics;

WriteLine("Please wait for the tasks to complete.");
Stopwatch watch = Stopwatch.StartNew();
Task a = Task.Factory.StartNew(MethodA);
Task b = Task.Factory.StartNew(MethodB);

Task.WaitAll(new Task[] { a, b });
watch.Stop();
WriteLine();
WriteLine("Results: {0}", SharedObjects.Message);
WriteLine($"{SharedObjects.Counter} string modifications.");
WriteLine("Time elapsed: {0:N0}ms.", watch.ElapsedMilliseconds);
