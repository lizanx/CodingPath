namespace ConfigWithDI.Services;

interface IGuidService
{
    IEnumerable<Guid> GetGuids(int count);
}
