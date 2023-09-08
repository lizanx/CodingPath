using Microsoft.AspNetCore.Mvc;

namespace DemoWebApi.Controllers;

[ApiController]
[Route("[controller]")]
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

    [HttpGet]
    public IActionResult GetAll()
    {
        return Ok(_fruits);
    }
    [HttpGet("{id}")]
    public IActionResult Get(int id)
    {
        if (id >= 0 && id < _fruits.Count())
        {
            return Ok(_fruits[id]);
        }
        return NotFound();
    }
}