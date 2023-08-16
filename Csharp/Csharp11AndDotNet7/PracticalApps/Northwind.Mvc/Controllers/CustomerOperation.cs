using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using Microsoft.EntityFrameworkCore;
using Northwind.Mvc.Models;
using Packt.Shared;
using Microsoft.AspNetCore.Mvc.Abstractions;

namespace Northwind.Mvc.Controllers;

public class CustomerOperationController : Controller
{
    private readonly ILogger<CustomerOperationController> _logger;
    // private readonly NorthwindContext _db;
    private readonly IHttpClientFactory _clientFactory;

    public CustomerOperationController(
        ILogger<CustomerOperationController> logger,
        // NorthwindContext injectedContext,
        IHttpClientFactory clientFactory)
    {
        _logger = logger;
        // _db = injectedContext;
        _clientFactory = clientFactory;
    }

    public IActionResult Index()
    {
        return View();
    }

    public async Task<IActionResult> Query(string customerId)
    {
        if (string.IsNullOrEmpty(customerId))
        {
            _logger.LogWarning($"Invalid CustomerId: {customerId}");
            return View();
        }

        HttpClient client = _clientFactory.CreateClient(name: "Northwind.WebApi");
        HttpRequestMessage request = new(method: HttpMethod.Get,
            requestUri: $"api/customers/{customerId}");
        HttpResponseMessage response = await client.SendAsync(request);
        Customer? model = await response.Content.ReadFromJsonAsync<Customer>();
        return View(model);
    }

    public async Task<IActionResult> Delete(string customerId)
    {
        HttpClient client = _clientFactory.CreateClient(name: "Northwind.WebApi");
        // HttpRequestMessage request = new(method: HttpMethod.Delete,
        //     requestUri: $"api/customers/{customerId}");
        HttpResponseMessage response = await client.DeleteAsync(
            requestUri: $"api/customers/{customerId}");
        // HttpResponseMessage response = await client.SendAsync(request);
        return View(response);
    }
}