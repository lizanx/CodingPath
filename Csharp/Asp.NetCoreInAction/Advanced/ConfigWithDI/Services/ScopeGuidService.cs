namespace ConfigWithDI.Services;

public class ScopeGuidService : IGuidService
{
    public IEnumerable<Guid> GetGuids(int count) =>
        Enumerable.Range(0, count).Select(_ => Guid.NewGuid());
}
