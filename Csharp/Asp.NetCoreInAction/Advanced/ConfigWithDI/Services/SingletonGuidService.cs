namespace ConfigWithDI.Services;

public class SingletonGuidService : IGuidService
{
    public IEnumerable<Guid> GetGuids(int count) =>
        Enumerable.Range(0, count).Select(_ => Guid.NewGuid());
}
