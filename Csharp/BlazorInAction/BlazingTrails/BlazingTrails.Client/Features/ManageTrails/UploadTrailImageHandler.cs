using MediatR;
using BlazingTrails.Shared.Features.ManageTrails;

namespace BlazingTrails.Client.Features.ManageTrails;

public class UploadTrailImageHandler(HttpClient httpClient) :
    IRequestHandler<UploadTrailImageRequest, UploadTrailImageRequest.Response>
{
    private readonly HttpClient _httpClient = httpClient;

    public async Task<UploadTrailImageRequest.Response> Handle(UploadTrailImageRequest request, CancellationToken cancellationToken)
    {
        var fileContent = request.File.OpenReadStream(request.File.Size, cancellationToken);
        using var content = new MultipartFormDataContent
        {
            { new StreamContent(fileContent), "image", request.File.Name }
        };
        
        var response = await _httpClient.PostAsync(
            UploadTrailImageRequest.RouteTemplate.Replace("{trailId}", request.TrailId.ToString()),
            content,
            cancellationToken);
        if (response.IsSuccessStatusCode)
        {
            var fileName = await response.Content.ReadAsStringAsync(cancellationToken: cancellationToken);
            return new UploadTrailImageRequest.Response(fileName);
        }
        return new UploadTrailImageRequest.Response("");
    }
}
