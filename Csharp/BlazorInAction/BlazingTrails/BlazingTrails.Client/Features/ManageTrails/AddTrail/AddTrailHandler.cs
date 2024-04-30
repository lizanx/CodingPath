using System.Net.Http.Json;
using BlazingTrails.Shared.Features.ManageTrails.AddTrail;
using MediatR;

namespace BlazingTrails.Client.Features.ManageTrails.AddTrail;

public class AddTrailHandler(HttpClient httpClient) : IRequestHandler<AddTrailRequest, AddTrailRequest.Response>
{
    public async Task<AddTrailRequest.Response> Handle(AddTrailRequest request, CancellationToken cancellationToken)
    {
        var response = await _httpClient.PostAsJsonAsync(AddTrailRequest.RouteTemplate, request, cancellationToken);
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

    private readonly HttpClient _httpClient = httpClient;
}
