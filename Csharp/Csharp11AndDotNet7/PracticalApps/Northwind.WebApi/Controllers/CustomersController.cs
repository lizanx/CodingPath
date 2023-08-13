using Microsoft.AspNetCore.Mvc;
using Packt.Shared;
using Northwind.WebApi.Repositories;

namespace Northwind.WebApi.Controllers;

// Base address: api/customers
[ApiController]
[Route("api/[controller]")]
public class CustomersController : ControllerBase
{
    private readonly ICustomerRepository repo;
    public CustomersController(ICustomerRepository repo)
    {
        this.repo = repo;
    }

    // GET: api/customers
    // GET: api/customers/?country=[country]
    [HttpGet]
    [ProducesResponseType(200, Type = typeof(IEnumerable<Customer>))]
    public async Task<IEnumerable<Customer>> GetCustomers(string? country)
    {
        if (string.IsNullOrWhiteSpace(country))
        {
            return await repo.RetrieveAllAsync();
        }
        else
        {
            return (await repo.RetrieveAllAsync()).Where(c => c.Country == country);
        }
    }

    // GET: api/customers/[id]
    [HttpGet("{id}", Name = nameof(GetCustomer))]
    [ProducesResponseType(200, Type = typeof(Customer))]
    [ProducesResponseType(404)]
    public async Task<IActionResult> GetCustomer(string id)
    {
        Customer? c = await repo.RetrieveAsync(id);
        if (c is null) return NotFound();
        return Ok(c); // 200 OK
    }

    // POST: api/customers
    // BODY: Customer(Json, XML)
    [HttpPost]
    [ProducesResponseType(201, Type = typeof(Customer))]
    [ProducesResponseType(400)]
    public async Task<IActionResult> Create([FromBody] Customer c)
    {
        if (c is null)
        {
            return BadRequest();
        }
        Customer? addedCustomer = await repo.CreateAsync(c);
        if (addedCustomer is null)
        {
            return BadRequest("Repository failed to create customer.");
        }
        else
        {
            return CreatedAtRoute( // 201 Created
              routeName: nameof(GetCustomer),
              routeValues: new { id = addedCustomer.CustomerId.ToLower() },
              value: addedCustomer);
        }
    }

    // PUT: api/customers/[id]
    // BODY: Customer(JSON, XML)
    [HttpPut("{id}")]
    [ProducesResponseType(204)]
    [ProducesResponseType(400)]
    [ProducesResponseType(404)]
    public async Task<IActionResult> Update(string id, [FromBody] Customer c)
    {
        id = id.ToUpper();
        if (c is null || c.CustomerId.ToUpper() != id) return BadRequest();
        c.CustomerId = c.CustomerId.ToUpper();

        Customer? exist = await repo.RetrieveAsync(id);
        if (exist is null) return NotFound();
        await repo.UpdateAsync(id, c);
        return new NoContentResult(); // 204 No Content
    }

    // DELETE: api/customers/[id]
    [HttpDelete("{id}")]
    [ProducesResponseType(204)]
    [ProducesResponseType(400)]
    [ProducesResponseType(404)]
    public async Task<IActionResult> Delete(string id)
    {
        // Take control of problem details.
        if (id == "bad")
        {
            ProblemDetails problemDetails = new()
            {
                Status = StatusCodes.Status400BadRequest,
                Type = "https://localhost:7074/customers/fail-to-delete",
                Title = $"Customer {id} found but failed to delte.",
                Detail = "More details like Company Name, Country and so on.",
                Instance = HttpContext.Request.Path
            };
            return BadRequest(problemDetails);
        }

        Customer? exist = await repo.RetrieveAsync(id);
        if (exist is null) return NotFound();

        bool? deleted = await repo.DeleteAsync(id);
        if (deleted is not null && deleted.Value)
        {
            return new NoContentResult(); // 204 No Content
        }
        else
        {
            return BadRequest($"Customer {id} was found but failed to delete.");
        }
    }
}