namespace TryObserverPattern;

public class Student : IObserver<SchoolClass>
{
    private IDisposable? _unsubscriber;

    public readonly string Name;

    public Student(string name)
    {
        Name = name;
    }

    public void OnNext(SchoolClass schoolClass)
    {
        Console.WriteLine(
            "{0} is taking class {1} which will last {2} minutes",
            Name,
            schoolClass.Subject,
            schoolClass.Duration.TotalMinutes
        );
    }

    public void OnError(Exception exception)
    {
        Console.WriteLine($"Student {Name} got an error: {exception}");
    }

    public void OnCompleted()
    {
        Console.WriteLine("{0} has finished all classes today, can go home now!", Name);
    }

    public void Subscribe(IObservable<SchoolClass> observable)
    {
        _unsubscriber = observable.Subscribe(this);
    }

    public void StopSchool()
    {
        _unsubscriber?.Dispose();
        _unsubscriber = null;
    }
}
