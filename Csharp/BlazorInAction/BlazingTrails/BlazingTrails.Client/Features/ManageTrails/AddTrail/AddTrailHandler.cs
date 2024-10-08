using System.Net.Http.Json;
using BlazingTrails.Shared.Features.ManageTrails.AddTrail;
using MediatR;

namespace BlazingTrails.Client.Features.ManageTrails.AddTrail;

public class AddTrailHandler(IHttpClientFactory httpClientFactory) : IRequestHandler<AddTrailRequest, AddTrailRequest.Response>
{
    public async Task<AddTrailRequest.Response> Handle(AddTrailRequest request, CancellationToken cancellationToken)
    {
        var client = _httpClientFactory.CreateClient("SecureAPIClient");
        var response = await client.PostAsJsonAsync(AddTrailRequest.RouteTemplate, request, cancellationToken);
        if (response.IsSuccessStatusCode)
        {
            var trailId = await response.Content.ReadFromJsonAsync<int>(cancellationToken);
            return new AddTrailRequest.Response(trailId);
        }
        else
        {
            return new AddTrailRequest.Response(-1);
        }
    }

    private readonly IHttpClientFactory _httpClientFactory = httpClientFactory;
}
