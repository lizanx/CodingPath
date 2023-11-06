1. Its id, processing time, memory usage...
2. Nanoseconds.
3. `Async`
4. `async`
5. `Task.Factory.StartNew` with option `TaskCreationOptions.AttachToParent`.
6. Because it's not very safe, may cause deadlocks.(Doesn't support timeout setting)
7. When you need the operation to be atomic, which means it cannot be interruptted.
8. When the sync is inter-process, not inter-thread.
9. It improves scalibity, but not the performance of a single request due to the  
overhead caused by thread switching.
10. Yes, by using a `CancellationToken`.
