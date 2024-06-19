namespace ApiConsumer;

public class UpperWordClientFactory
{
    private readonly IServiceProvider _serviceProvider;

    public UpperWordClientFactory(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }

    public UpperWordClient CreateClient()
    {
        return _serviceProvider.GetRequiredService<UpperWordClient>();
    }
}
