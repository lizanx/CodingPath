using System.ComponentModel.DataAnnotations;
using TryValidationAttribute.Services;

namespace TryValidationAttribute.ValidationAttributes;

public class LanguageValidationAttribute : ValidationAttribute
{
    public readonly string[] _userAllowedLanguages;

    public LanguageValidationAttribute(params string[] allowedLanguages)
    {
        _userAllowedLanguages = allowedLanguages;
    }

    protected override ValidationResult? IsValid(object? value, ValidationContext validationContext)
    {
        if (value is string language)
        {
            if (_userAllowedLanguages.Contains(language))
            {
                return ValidationResult.Success;
            }

            var allowedLanguageService = validationContext.GetRequiredService<AllowedLanguageService>()!;
            if (allowedLanguageService.IsLanguageAllowed(language))
            {
                return ValidationResult.Success;
            }
        }

        return new ValidationResult($"Unknown language: {value?.ToString()}");
    }
}
