using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using FruitWebApp.Models;
using System.Text.Json;
using Microsoft.AspNetCore.Components;
using System.Text;
using System.Diagnostics;


namespace FruitWebApp.Pages
{
    public class AddModel : PageModel
    {
        // IHttpClientFactory set using dependency injection 
        private readonly IHttpClientFactory _httpClientFactory;

        public AddModel(IHttpClientFactory httpClientFactory) => _httpClientFactory = httpClientFactory;

        // Add the data model and bind the form data to the page model properties
        [BindProperty]
        public FruitModel FruitModels { get; set; } = default!;

        public async Task<IActionResult> OnPost()
        {
            var client = _httpClientFactory.CreateClient("FruitAPI") ?? throw new InvalidOperationException("Failed to create http client");

            using var response = await client.PostAsJsonAsync("", FruitModels);
            if (response?.IsSuccessStatusCode ?? false)
            {
                TempData["success"] = "Data was added successfully.";
                return RedirectToPage("Index");
            }
            else
            {
                TempData["failure"] = "Operation was not successful";
                return RedirectToPage("Index");
            }
        }
    }
}

