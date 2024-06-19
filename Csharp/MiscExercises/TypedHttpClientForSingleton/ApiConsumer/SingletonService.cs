namespace ApiConsumer;

public class SingletonService
{
    private readonly UpperWordClient _client;

    // The UpperWordClient registered with AddHttpClient is of transient lifetime.
    // Thus it's dangerous to inejct in into singleton service.
    // The typed client is out of client factory/pool's control once it's created.
    // If singleton service holds reference to the typed client, then its lifetime becomes singleton.
    // That may cause not-reflecting-DNS-update issue.
    public SingletonService(UpperWordClient upperWordClient)
    {
        _client = upperWordClient;
    }

    public async Task<string> GetUpperWordAsync(string word)
    {
        string upper = await _client.GetUpperWordAsync(word);

        return upper;
    }
}
