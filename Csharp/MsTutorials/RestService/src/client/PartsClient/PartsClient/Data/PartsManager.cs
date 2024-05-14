using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace PartsClient.Data;

public static class PartsManager
{
    // TODO: Add fields for BaseAddress, Url, and authorizationKey
    static readonly string BaseAddress = "http://mslearnpartsserver1427120750.azurewebsites.net";
    static readonly string Url = $"{BaseAddress}/api/";
    private static string authorizationKey;

    static HttpClient client;

    private static async Task<HttpClient> GetClient()
    {
        if (client is not null) return client;

        client = new HttpClient();

        if (string.IsNullOrEmpty(authorizationKey) )
        {
            authorizationKey = JsonSerializer.Deserialize<string>(await client.GetStringAsync($"{Url}login"));
        }

        client.DefaultRequestHeaders.Add("Authorization", authorizationKey);
        client.DefaultRequestHeaders.Add("Accept", "application/json");

        return client;
    }

    public static async Task<IEnumerable<Part>> GetAll()
    {
        if (Connectivity.Current.NetworkAccess != NetworkAccess.Internet) return [];

        var client = await GetClient();

        return await client.GetFromJsonAsync<List<Part>>($"{Url}parts", new JsonSerializerOptions { PropertyNameCaseInsensitive = true });
    }

    public static async Task<Part> Add(string partName, string supplier, string partType)
    {
        if (Connectivity.Current.NetworkAccess != NetworkAccess.Internet) return new();

        var part = new Part()
        {
            PartName = partName,
            Suppliers = new List<string>(new[] { supplier }),
            PartID = string.Empty,
            PartType = partType,
            PartAvailableDate = DateTime.Now.Date
        };
        var msg = new HttpRequestMessage(HttpMethod.Post, $"{Url}parts");
        msg.Content = JsonContent.Create(part);

        var client = await GetClient();
        var response = await client.SendAsync(msg);
        response.EnsureSuccessStatusCode();
        return await JsonSerializer.DeserializeAsync<Part>(await response.Content.ReadAsStreamAsync(),
            new JsonSerializerOptions { PropertyNameCaseInsensitive = true });
    }

    public static async Task Update(Part part)
    {
        if (Connectivity.Current.NetworkAccess != NetworkAccess.Internet) return;

        var request = new HttpRequestMessage(HttpMethod.Put, $"{Url}parts/{part.PartID}");
        request.Content = JsonContent.Create(part);

        var client = await GetClient();
        var response = await client.SendAsync(request);
        response.EnsureSuccessStatusCode();
    }

    public static async Task Delete(string partID)
    {
        if (Connectivity.Current.NetworkAccess != NetworkAccess.Internet) return;

        var request = new HttpRequestMessage(HttpMethod.Delete, $"{Url}parts/{partID}");
        var client = await GetClient();
        var response = await client.SendAsync(request);
        response.EnsureSuccessStatusCode();
    }
}
