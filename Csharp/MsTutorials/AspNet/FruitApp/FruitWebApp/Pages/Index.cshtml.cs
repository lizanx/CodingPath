using Microsoft.AspNetCore.Mvc.RazorPages;
using FruitWebApp.Models;
using System.Text.Json;
using Microsoft.Net.Http.Headers;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Mvc;

namespace FruitWebApp.Pages
{
    public class IndexModel : PageModel
    {
        // IHttpClientFactory set using dependency injection 
        private readonly IHttpClientFactory _httpClientFactory;

        public IndexModel(IHttpClientFactory httpClientFactory)
        {
            _httpClientFactory = httpClientFactory;
        }

        // Add the data model and bind the form data to the page model properties
        // Enumerable since an array is expected as a response
        [BindProperty]
        public IEnumerable<FruitModel> FruitModels { get; set; } = default!;

        public async Task OnGet()
        {
            var client = _httpClientFactory.CreateClient("FruitAPI");
            if (client is null) return;

            using var response = await client.GetAsync("");
            if (response?.IsSuccessStatusCode ?? false)
            {
                FruitModels = await response.Content.ReadFromJsonAsync<List<FruitModel>>() ?? new List<FruitModel>();
            }
        }
    }
}

