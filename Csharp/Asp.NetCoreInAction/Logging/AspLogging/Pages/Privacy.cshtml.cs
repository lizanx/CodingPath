using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace AspLogging.Pages;

public class PrivacyModel : PageModel
{
    private readonly ILogger<PrivacyModel> _logger;

    public PrivacyModel(ILogger<PrivacyModel> logger)
    {
        _logger = logger;
    }

    public void OnGet()
    {
        using (_logger.BeginScope("Privacy Scope"))
        {
            using (_logger.BeginScope(new Dictionary<string, object>
            {
                {"Name", "Chris"},
                {"Age", 19},
                {"Career", "Engineer"}
            }))
            {
                _logger.LogInformation("My favorite programming language is {FaviriteLang}", "C#");
            }
        }
    }
}

