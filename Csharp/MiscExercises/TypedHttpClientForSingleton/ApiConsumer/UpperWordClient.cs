namespace ApiConsumer;

public class UpperWordClient
{
    private readonly HttpClient _client;

    private readonly ILogger<UpperWordClient> _logger;

    public UpperWordClient(HttpClient client, ILogger<UpperWordClient> logger)
    {
        _client = client;
        _client.BaseAddress = new Uri("https://localhost:7199/");
        _logger = logger;
    }

    public async Task<string> GetUpperWordAsync(string word)
    {
        var response = await _client.GetAsync($"/{word}");

        response.EnsureSuccessStatusCode();

        string upperWord = await response.Content.ReadAsStringAsync();

        return upperWord;
    }
}
