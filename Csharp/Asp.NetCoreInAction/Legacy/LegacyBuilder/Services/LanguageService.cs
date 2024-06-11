using System.Collections;

namespace LegacyBuilder.Services;

public class LanguageService
{
    private readonly string[] _languages =
    [
        "C",
        "C++",
        "C#",
        "Go",
        "Zig",
        "Kotlin",
        "Python",
        "Javascript"
    ];

    public string[] GetLanguages(int count) =>
        Enumerable.Range(0, count).Select(_ => _languages[Random.Shared.Next(_languages.Length)]).ToArray();
}
