using LegacyBuilder.Services;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace LegacyBuilder.Pages;

public class IndexPageModel : PageModel
{
    private readonly LanguageService _languageService;
    public IndexPageModel(LanguageService languageService)
    {
        _languageService = languageService;
    }

    public string[] GetLanguages(int count) =>
        _languageService.GetLanguages(count);
}
