using FluentValidation;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace TryFluentValidation.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;
    private readonly IValidator<InputModel> _validator;

    [BindProperty]
    public InputModel Input { get; set; } = new();

    public bool IsInputValid { get; set; }

    public IndexModel(ILogger<IndexModel> logger, IValidator<InputModel> validator)
    {
        _logger = logger;
        _validator = validator;
    }

    public class InputModel
    {
        public string Name { get; set; } = default!;
        public int Age { get; set; }
    }

    public class InputModelValidator : AbstractValidator<InputModel>
    {
        public InputModelValidator()
        {
            RuleFor(x => x.Name)
                .NotEmpty()
                .Length(3, 100)
                .WithMessage("Invalid name: must be non-empty and length among [3,100]");
            
            RuleFor(x => x.Age)
                .Must(age => age >= 0 && age <= 150)
                .WithMessage("Invalid age: must be amonge [0, 150]");
        }
    }

    public void OnGet()
    {

    }

    public IActionResult OnPost()
    {
        var validateResult = _validator.Validate(Input);
        if (validateResult.IsValid)
        {
            IsInputValid = true;
            return Page();
        }
        else
        {
            IsInputValid = false;
            foreach (var error in validateResult.Errors)
            {
                // Console.WriteLine("Key: {0}, Value: {1}", error!.PropertyName, error!.ErrorMessage);
                ModelState.AddModelError(nameof(Input) + "." + error!.PropertyName, error!.ErrorMessage);
            }

            return Page();
        }
    }
}
