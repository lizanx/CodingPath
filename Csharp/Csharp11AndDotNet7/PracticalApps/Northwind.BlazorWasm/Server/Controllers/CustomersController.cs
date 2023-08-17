using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Packt.Shared;

namespace Northwind.BlazorWasm.Server.Controllers;

// TODO: this fails because BlazorWasm won't link in local ref to Northwind.Common.DataContext.Sqlite
[ApiController]
[Route("api/[controller]")]
public class CustomersController : ControllerBase
{
    private readonly NorthwindContext db;

    public CustomersController(NorthwindContext db)
    {
        this.db = db;
    }

    [HttpGet]
    public async Task<List<Customer>> GetCustomersAsync()
    {
        return await db.Customers.ToListAsync();
    }
    [HttpGet("in/{country}")]
    public async Task<List<Customer>> GetCustomersAsync(string country)
    {
        return await db.Customers.Where( c => c.Country == country ).ToListAsync();
    }
    [HttpGet("{id}")]
    public async Task<Customer?> GetCustomerAsync(string id)
    {
        return await db.Customers.FirstOrDefaultAsync( c => c.CustomerId == id );
    }
    [HttpPost]
    public async Task<Customer?> CreateCustomerAsync(Customer customerToAdd)
    {
        Customer? existing = await db.Customers.FirstOrDefaultAsync( c => c.CustomerId == customerToAdd.CustomerId );
        if (existing is null)
        {
            db.Customers.Add(customerToAdd);
            int affected = await db.SaveChangesAsync();
            if (affected == 1)
            {
                return customerToAdd;
            }
        }
        return existing;
    }
    [HttpPut]
    public async Task<Customer?> UpdateCustomerAsync(Customer c)
    {
        db.Entry(c).State = EntityState.Modified;
        int affected = await db.SaveChangesAsync();
        if (affected == 1)
        {
            return c;
        }
        return null;
    }
    [HttpDelete("id")]
    public async Task<int> DeleteCustomerAsync(string id)
    {
        Customer? existing = await db.Customers.FirstOrDefaultAsync( c => c.CustomerId == id );
        if (existing is not null)
        {
            db.Customers.Remove(existing);
            return await db.SaveChangesAsync();
        }
        return 0;
    }

}