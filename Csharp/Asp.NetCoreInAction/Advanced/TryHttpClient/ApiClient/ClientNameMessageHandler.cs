
namespace ApiClient;

public class ClientNameMessageHandler : DelegatingHandler
{
    protected override Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
    {
        request.Headers.Add("ClientName", "api-client");
        return base.SendAsync(request, cancellationToken);
    }
}
