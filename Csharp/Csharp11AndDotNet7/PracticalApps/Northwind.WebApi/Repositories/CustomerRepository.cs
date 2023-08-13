using Microsoft.EntityFrameworkCore.ChangeTracking; // EntityEntry<T>
using System.Collections.Concurrent; // ConcurrentDictionary
using Packt.Shared;

namespace Northwind.WebApi.Repositories;

public class CustomerRepository : ICustomerRepository
{
    // Use a static thread-safe dictionary to cache the customers.
    private static ConcurrentDictionary<string, Customer>? customerCache;
    // Use an instance data context field because it shouldn't be cached
    // due to the data context having internal caching.
    private NorthwindContext db;

    public CustomerRepository(NorthwindContext injectedContext)
    {
        db = injectedContext;

        // Preload customers from database as a normal dictionary with CustomerId as the key.
        // Then convert it to a thread-safe ConcurrentDictionary.
        if (customerCache is null)
        {
            customerCache = new(db.Customers.ToDictionary( c => c.CustomerId ));
        }
    }

    private Customer UpdateCache(string id, Customer c)
    {
        Customer? old;
        if (customerCache is not null)
        {
            if (customerCache.TryGetValue(id, out old))
            {
                if (customerCache.TryUpdate(id, c, old))
                {
                    return c;
                }
            }
        }
        return null!;
    }

    public async Task<Customer?> CreateAsync(Customer c)
    {
        c.CustomerId = c.CustomerId.ToUpper();
        EntityEntry<Customer> added = db.Add(c);
        int affected = await db.SaveChangesAsync();
        if (affected == 1)
        {
            if (customerCache is null) return c;
            return customerCache.AddOrUpdate(c.CustomerId, c, UpdateCache);
        }
        else
        {
            return null;
        }
    }

    public  Task<IEnumerable<Customer>> RetrieveAllAsync()
    {
        // Get from cache for performance consideration.
        return Task.FromResult(customerCache is null
            ? Enumerable.Empty<Customer>() : customerCache.Values);
    }

    public Task<Customer?> RetrieveAsync(string id)
    {
        id = id.ToUpper();
        if (customerCache is null) return null!;
        customerCache.TryGetValue(id, out Customer? c);
        return Task.FromResult(c);
    }

    public async Task<Customer?> UpdateAsync(string id, Customer c)
    {
        id = id.ToUpper();
        c.CustomerId = c.CustomerId.ToUpper();

        db.Customers.Update(c);
        int affected = await db.SaveChangesAsync();
        if (affected == 1)
        {
            return UpdateCache(id, c);
        }
        return null;
    }

    public async Task<bool?> DeleteAsync(string id)
    {
        id = id.ToUpper();

        Customer? c = db.Customers.Find(id);
        if (c is null) return null;
        db.Customers.Remove(c);
        int affected = await db.SaveChangesAsync();
        if (affected == 1)
        {
            if (customerCache is null) return null;
            return customerCache.TryRemove(id, out c);
        }
        return null;
    }
}