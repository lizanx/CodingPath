using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace ApiConsumer.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;

    // private readonly SingletonService _singletonService;
    private readonly UpperWordClientFactory _clientFactory;

    public List<string> UpperWords = [];

    public IndexModel(ILogger<IndexModel> logger,
        // SingletonService singletonService)
        UpperWordClientFactory upperWordClientFactory)
    {
        _logger = logger;
        // _singletonService = singletonService;
        _clientFactory = upperWordClientFactory;
    }

    public async Task OnGet()
    {
        // string hello = await _singletonService.GetUpperWordAsync("hello");
        // string world = await _singletonService.GetUpperWordAsync("world");

        var client = _clientFactory.CreateClient();
        var hello = await client.GetUpperWordAsync("hello");
        var world = await client.GetUpperWordAsync("world");
        UpperWords.Add(hello);
        UpperWords.Add(world);
    }
}
