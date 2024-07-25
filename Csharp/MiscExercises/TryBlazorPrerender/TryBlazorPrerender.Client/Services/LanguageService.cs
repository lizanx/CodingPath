namespace TryBlazorPrerender.Client.Services;

public class LanguageService
{
    private readonly string[] _languages =
    [
        "C#",
        "C++",
        "Go",
        "Python",
        "Javascript",
        "Kotlin",
        "Swift",
        "Zig"
    ];

    public IEnumerable<string> GetLanguages(int count)
    {
        return Enumerable
            .Range(0, count)
            .Select(_ => _languages[Random.Shared.Next(_languages.Length)])
            .ToArray();
    }
}
