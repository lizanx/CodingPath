using Microsoft.AspNetCore.Mvc.Filters;

namespace DemoWebApi.Filters;

public class LogResourceFilter : Attribute, IResourceFilter
{
    private readonly int _order; // Log the order of filter executions from different scopes.
    public LogResourceFilter(int order)
    {
        _order = order;
    }
    public void OnResourceExecuting(ResourceExecutingContext ctx)
    {
        Console.WriteLine($"LogResourceFilter[{_order}]::OnResourceExecuting");
    }

    public void OnResourceExecuted(ResourceExecutedContext ctx)
    {
        Console.WriteLine($"LogResourceFilter[{_order}]::OnResourceExecuted");
    }
}