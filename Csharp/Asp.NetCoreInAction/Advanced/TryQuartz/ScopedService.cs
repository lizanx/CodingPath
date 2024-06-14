namespace TryQuartz;

public class ScopedService
{
    private readonly List<string> _languages =
    [
        "C#",
        "C++",
        "Golang",
        "Python",
        "Javascript",
        "Zig",
        "Rust",
        "Kotlin",
        "Swift",
        "Lua"
    ];

    public IEnumerable<string> GetLanguages(int count = 3) =>
        Enumerable.Range(0, count).Select(_ => _languages[Random.Shared.Next(_languages.Count)]);
}
