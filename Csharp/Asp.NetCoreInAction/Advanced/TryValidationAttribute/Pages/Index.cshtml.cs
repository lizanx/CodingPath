using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using TryValidationAttribute.ValidationAttributes;

namespace TryValidationAttribute.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;

    public string SelectedLanguage = string.Empty;

    [BindProperty]
    public InputModel Input { get; set; }

    public IndexModel(ILogger<IndexModel> logger)
    {
        _logger = logger;
        Input = new();
    }

    public class InputModel
    {
        [LanguageValidation("Cpp", "Csharp")]
        public string Language { get; set; } = default!;
    }

    public void OnGet()
    {

    }

    public void OnPost()
    {
        SelectedLanguage = Input.Language;
    }
}
