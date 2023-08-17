using System.Net.Http;
using System.Net.Http.Json;
using Packt.Shared;

namespace Northwind.BlazorWasm.Client.Data;

public class NorthwindService : INorthwindService
{
    private readonly HttpClient http;
    public NorthwindService(HttpClient http)
    {
        this.http = http;
    }

    public Task<List<Customer>> GetCustomersAsync()
    {
        return http.GetFromJsonAsync<List<Customer>>(requestUri: "api/customers")!;
    }
    public Task<List<Customer>> GetCustomersAsync(string country)
    {
        return http.GetFromJsonAsync<List<Customer>>(requestUri: $"api/customers/in/{country}")!;
    }
    public Task<Customer?> GetCustomerAsync(string id)
    {
        return http.GetFromJsonAsync<Customer>(requestUri: $"api/customers/{id}");
    }
    public async Task<Customer> CreateCustomerAsync(Customer c)
    {
        HttpResponseMessage response = await http.PostAsJsonAsync(requestUri: "api/customers", c);
        return (await response.Content.ReadFromJsonAsync<Customer>())!;
    }
    public async Task<Customer> UpdateCustomerAsync(Customer c)
    {
        HttpResponseMessage response = await http.PutAsJsonAsync(requestUri: "api/customers", c);
        return (await response.Content.ReadFromJsonAsync<Customer>())!;
    }
    public async Task DeleteCustomerAsync(string id)
    {
        await http.DeleteAsync(requestUri: $"api/customers/{id}");
    }

}