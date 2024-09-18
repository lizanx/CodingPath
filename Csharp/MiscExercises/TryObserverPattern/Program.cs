using TryObserverPattern;

var s1 = new Student("Kevin");
var s2 = new Student("Jason");
var timetable = new Timetable();

s1.Subscribe(timetable);
timetable.ArrangeClass(new SchoolClass("Math", TimeSpan.FromMinutes(30)));
timetable.ArrangeClass(new SchoolClass("English", TimeSpan.FromMinutes(35)));
s2.Subscribe(timetable);
timetable.ArrangeClass(new SchoolClass("Philosophy", TimeSpan.FromMinutes(50)));
timetable.ArrangeClass(new SchoolClass("Programming", TimeSpan.FromMinutes(120)));
s1.StopSchool();
timetable.ArrangeClass(new SchoolClass("Literature", TimeSpan.FromMinutes(70)));
timetable.FinishSchedule();
timetable.ShowObserverCount();
