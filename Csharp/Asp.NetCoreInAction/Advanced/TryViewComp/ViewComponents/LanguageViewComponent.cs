using Microsoft.AspNetCore.Mvc;
using TryViewComp.Services;

namespace TryViewComp.ViewComponents;

public class LanguageViewComponent : ViewComponent
{
    private readonly LanguageService _languageService;

    // It's fine to inject services into view component's ctor.
    public LanguageViewComponent(LanguageService languageService)
    {
        _languageService = languageService;
    }

    public Task<IViewComponentResult> InvokeAsync(int languagesCount)
    {
        if (languagesCount < 3)
        {
            return Task.FromResult<IViewComponentResult>(View("TooFew"));
        }

        var languages = _languageService.GetLanguages(languagesCount);

        return Task.FromResult<IViewComponentResult>(View("Languages", languages));
    }
}
