using System.Net.Http.Json;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using MediatR;

namespace BlazingTrails.Client.Features.ManageTrails.EditTrail;

public class EditTrailHandler(HttpClient httpClient) :
    IRequestHandler<EditTrailRequest, EditTrailRequest.Response>
{
    private readonly HttpClient _httpClient = httpClient;

    public async Task<EditTrailRequest.Response> Handle(EditTrailRequest request, CancellationToken cancellationToken)
    {
        var response = await _httpClient.PutAsJsonAsync(EditTrailRequest.RouteTemplate, request, cancellationToken);
        if (response == null || !response.IsSuccessStatusCode)
        {
            return new EditTrailRequest.Response(false);
        }
        else
        {
            return new EditTrailRequest.Response(true);
        }
    }
}
