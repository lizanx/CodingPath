using Microsoft.AspNetCore.Mvc.Filters;

namespace DemoWebApi.Filters;

public class PriorityFilter : Attribute, IResourceFilter, IOrderedFilter
{
    public void OnResourceExecuting(ResourceExecutingContext ctx)
    {
        Console.WriteLine($"PriorityFilter::OnResourceExecuting");
    }

    public void OnResourceExecuted(ResourceExecutedContext ctx)
    {
        Console.WriteLine($"PriorityFilter::ResourceExecutedContext");
    }

    public int Order
    {
        get
        {
            return -1;
        }
    }
}