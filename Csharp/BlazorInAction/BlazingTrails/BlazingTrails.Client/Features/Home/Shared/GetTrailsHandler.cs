using System.Net.Http.Json;
using BlazingTrails.Shared.Features.Home.Shared;
using MediatR;

namespace BlazingTrails.Client.Features.Home.Shared;

public class GetTrailsHandler(HttpClient httpClient) :
    IRequestHandler<GetTrailsRequest, GetTrailsRequest.Response?>
{
    private readonly HttpClient _httpClient = httpClient;

    public async Task<GetTrailsRequest.Response?> Handle(GetTrailsRequest request, CancellationToken cancellationToken)
    {
        try
        {
            return await _httpClient.GetFromJsonAsync<GetTrailsRequest.Response>(GetTrailsRequest.RouteTemplate, cancellationToken: cancellationToken);
        }
        catch (HttpRequestException)
        {
            return default!;
        }
    }
}
