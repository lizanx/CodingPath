using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace TryFinbuckleHtml5Validation.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;
    
    [BindProperty]
    public InputModel Input { get; set; }

    public IndexModel(ILogger<IndexModel> logger)
    {
        _logger = logger;
        Input = new();
    }

    public void OnGet()
    {

    }

    public IActionResult OnPost()
    {
        if (!ModelState.IsValid)
        {
            _logger.LogError("Invalid model for POST!");
            return Page();
        }

        _logger.LogInformation("Accepted POST: Name={0}, Age={1}, PhoneNumber={2}",
                Input.Name, Input.Age, Input.PhoneNumber);

        return Page();
    }

    public class InputModel
    {
        [Required, MinLength(3, ErrorMessage = "Your name must contain at least 3 characters")]
        public string Name { get; set; } = default!;

        [Range(0, 100, ErrorMessage = "You age must between 0~100")]
        public int Age { get; set; }

        [MinLength(11, ErrorMessage = "Too short"), MaxLength(11, ErrorMessage = "Too long")]
        public string PhoneNumber { get; set; } = default!;
    }
}
