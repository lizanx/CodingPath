using System.Collections.Generic;

namespace GetStartedApp.Services;

public interface IDataAccessService<T>
{
    IEnumerable<T>? GetAll();
}