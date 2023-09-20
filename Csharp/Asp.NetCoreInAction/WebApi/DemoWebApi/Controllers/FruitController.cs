using Microsoft.AspNetCore.Mvc;
using DemoWebApi.Filters;

namespace DemoWebApi.Controllers;

[ApiController]
[Route("[controller]")]
[LogResourceFilter(2)] // Add Controller-Scope filter
public class FruitController : ControllerBase
{
    private List<string> _fruits = new()
    {
        "Apple",
        "Banana",
        "Pear",
        "Peach",
        "Grape",
        "Watermelon",
        "Orange",
        "Strawbeery",
    };

    [LogResourceFilter(3)] // Add Action-Scope filter
    [PriorityFilter]
    [HttpGet]
    public IActionResult GetAll()
    {
        return Ok(_fruits);
    }
    [HttpGet("{id}")]
    public IActionResult Get(int id, ILogger<FruitController> _logger)
    {
        _logger.LogInformation("Get all fruits, logging without any scope");
        using (_logger.BeginScope("Scope Value 1"))
        {
            _logger.LogInformation("Get all fruits, logging with a list of scope values");
        }
        using (_logger.BeginScope(new Dictionary<string, string> { {"ScopeLogging", "DictState"} }))
        {
            _logger.LogInformation("Get all fruits, logging with Dict scope");
        }

        if (id >= 0 && id < _fruits.Count)
        {
            return Ok(_fruits[id]);
        }
        return NotFound();
    }
}