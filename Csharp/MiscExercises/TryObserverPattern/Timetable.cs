namespace TryObserverPattern;

public class Timetable : IObservable<SchoolClass>
{
    private readonly List<SchoolClass> _schoolClasses = [];
    private readonly List<IObserver<SchoolClass>> _observers = [];

    public IDisposable Subscribe(IObserver<SchoolClass> observer)
    {
        _observers.Add(observer);
        if (_schoolClasses.Count > 0)
        {
            foreach (var schoolClass in _schoolClasses)
            {
                observer.OnNext(schoolClass);
            }
        }

        return new TimetableUnsubscriber(_observers, observer);
    }

    public void ArrangeClass(SchoolClass? schoolClass)
    {
        if (schoolClass is null)
        {
            var e = new ArgumentNullException("Invalid null class added");
            foreach (var observer in _observers)
            {
                observer.OnError(e);
            }
            return;
        }

        _schoolClasses.Add(schoolClass);
        foreach (var observer in _observers)
        {
            observer.OnNext(schoolClass);
        }
    }

    public void FinishSchedule()
    {
        foreach (var observer in _observers)
        {
            observer.OnCompleted();
        }
        _observers.Clear();
    }

    public class TimetableUnsubscriber : IDisposable
    {
        private readonly List<IObserver<SchoolClass>> _subscribers;
        private readonly IObserver<SchoolClass> _subscriber;

        public TimetableUnsubscriber(
            List<IObserver<SchoolClass>> subscribers,
            IObserver<SchoolClass> subscriber
        )
        {
            _subscribers = subscribers;
            _subscriber = subscriber;
        }

        public void Dispose()
        {
            _subscribers.Remove(_subscriber);
        }
    }

    public void ShowObserverCount()
    {
        Console.WriteLine("Count of subscribers: {0}", _observers.Count);
    }
}
