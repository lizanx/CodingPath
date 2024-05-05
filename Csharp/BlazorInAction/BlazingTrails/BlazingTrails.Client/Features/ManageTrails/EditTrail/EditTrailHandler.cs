using System.Net.Http.Json;
using BlazingTrails.Shared.Features.ManageTrails.EditTrail;
using MediatR;

namespace BlazingTrails.Client.Features.ManageTrails.EditTrail;

public class EditTrailHandler(IHttpClientFactory httpClientFactory) :
    IRequestHandler<EditTrailRequest, EditTrailRequest.Response>
{
    private readonly IHttpClientFactory _httpClientFactory = httpClientFactory;

    public async Task<EditTrailRequest.Response> Handle(EditTrailRequest request, CancellationToken cancellationToken)
    {
        var client = _httpClientFactory.CreateClient("SecureAPIClient");
        var response = await client.PutAsJsonAsync(EditTrailRequest.RouteTemplate, request, cancellationToken);
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
