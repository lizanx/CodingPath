namespace TryViewComp.Services;

public class LanguageService
{
    private static readonly List<string> _languages =
    [
        "C++",
        "Csharp",
        "Go",
        "Python",
        "Zig",
        "Kotlin",
        "Swift"
    ];

    public IEnumerable<string> GetLanguages(int count) =>
        Enumerable.Range(0, count).Select(_ => _languages[Random.Shared.Next(_languages.Count)]).ToList();
}
