namespace TryValidationAttribute.Services;

public class AllowedLanguageService
{
    private static readonly List<string> _allowedLanguages =
    [
        "C++",
        "C#",
        "Go",
        "Python",
        "Javascript"
    ];

    public bool IsLanguageAllowed(string language) =>
        _allowedLanguages.Contains(language);

    public string GetLanguageDescription(string language) =>
        language switch
        {
            "C++" or "Cpp" => "A compiled static language derived from C",
            "C#" or "Csharp" => "A static CLR language from Microsoft",
            "Go" => "A static concurrency-focused language from Google",
            "Python" => "A widely used dynamic language",
            "Javascript" => "A widely used dynamic language for browser",
            _ => "Unknown language"
        };
}
