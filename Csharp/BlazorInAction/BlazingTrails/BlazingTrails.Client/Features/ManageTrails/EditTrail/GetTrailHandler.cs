using System.Net.Http.Json;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using MediatR;

namespace BlazingTrails.Client.Features.ManageTrails.EditTrail;

public class GetTrailHandler(IHttpClientFactory httpClientFactory) :
    IRequestHandler<GetTrailRequest, GetTrailRequest.Response?>
{
    private readonly IHttpClientFactory _httpClientFactory = httpClientFactory;

    public async Task<GetTrailRequest.Response?> Handle(GetTrailRequest request, CancellationToken cancellationToken)
    {
        try
        {
            var client = _httpClientFactory.CreateClient("SecureAPIClient");
            return await client.GetFromJsonAsync<GetTrailRequest.Response>(
                GetTrailRequest.RouteTemplate.Replace("{trailId}", request.TrailId.ToString()), cancellationToken);
        }
        catch (HttpRequestException)
        {
            return default!;
        }
    }
}