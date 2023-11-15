using Microsoft.Extensions.Localization; // IStringLocalizer, LocalizedString

public class PacktResources
{
    private readonly IStringLocalizer<PacktResources> localizer = null!;

    public PacktResources(IStringLocalizer<PacktResources> localizer)
    {
        this.localizer = localizer;
    }

    public string? GetEnterYourNamePrompt()
    {
        string resourceStringName = "EnterYourName";

        LocalizedString localizedString = localizer[resourceStringName];

        if (localizedString.ResourceNotFound)
        {
            ConsoleColor prevColor = ForegroundColor;
            ForegroundColor = ConsoleColor.Red;
            WriteLine($"Error: resource string \"{resourceStringName}\" not found."
                + $"{Environment.NewLine}Search path: {localizedString.SearchedLocation}");
            ForegroundColor = prevColor;

            return $"{resourceStringName}";
        }

        // LocalizedString has an implicit cast to string.
        return localizedString;
    }

    public string? GetEnterYourDobPrompt()
    {
        // LocalizedString falls back to the key if resource string is not found.
        return localizer["EnterYourDob"];
    }

    public string? GetEnterYourSalaryPrompt()
    {
        return localizer["EnterYourSalary"];
    }

    public string? GetPersonDetails(
        string name, DateTime dob, int minutes, decimal salary)
    {
        return localizer["PersonDetails", name, dob, minutes, salary];
    }
}