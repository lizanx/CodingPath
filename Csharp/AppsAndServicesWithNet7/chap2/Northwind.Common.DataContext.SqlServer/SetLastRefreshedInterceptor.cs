using Microsoft.EntityFrameworkCore.Diagnostics;

namespace Packt.Shared;

public class SetLastRefreshedInterceptor : IMaterializationInterceptor
{
    public object InitializedInstance(
        MaterializationInterceptionData materializationInterceptionData,
        object entity)
    {
        if (entity is IHasLastRefreshed entityWithLastRefreshed)
        {
            entityWithLastRefreshed.LastRefreshed = DateTimeOffset.UtcNow;
        }
        return entity;
    }
}