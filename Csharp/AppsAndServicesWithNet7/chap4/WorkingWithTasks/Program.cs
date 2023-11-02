using System.Diagnostics;

OutputThreadInfo();
Stopwatch timer = Stopwatch.StartNew();

/*
SectionTitle("Running methods synchronously on one thread.");
MethodA();
MethodB();
MethodC();
*/

/*
SectionTitle("Running methods asynchronously on multiple threads.");
Task taskA = new(MethodA);
taskA.Start();
Task taskB = Task.Factory.StartNew(MethodB);
Task taskC = Task.Run(MethodC);
Task[] tasks = new[]{ taskA, taskB, taskC };
WriteLine("Waiting for tasks to finish...");
Task.WaitAll(tasks);
*/

/*
SectionTitle("Passing the result of one task as an input into another.");
timer.Restart();
Task<string> taskServiceThenSProc = Task.Factory
    .StartNew(CallWebService)
    .ContinueWith(previousTask =>
        CallStoredProcedure(previousTask.Result));
timer.Stop();
WriteLine($"Result: {taskServiceThenSProc.Result}");
*/

SectionTitle("Nested and child tasks");
Task outerTask = Task.Factory.StartNew(OuterMethod);
outerTask.Wait();
WriteLine("Console app is stopping.");

WriteLine($"{timer.ElapsedMilliseconds:#,##0}ms elapsed.");
