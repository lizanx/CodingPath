namespace AgeCalculator;

public class AgeCalculator
{
    private readonly DateTime _birthDateTime;

    public AgeCalculator(DateTime birthDateTime)
    {
        _birthDateTime = birthDateTime;
    }

    public int Years =>
        DateTime.Now.Year - _birthDateTime.Year;
}
